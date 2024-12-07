/***************************************************************************** 
 * Includes
 ****************************************************************************/
#include <stdio.h>		
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <X11/Xlibint.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/cursorfont.h>
#include <X11/keysymdef.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "chartbl.h"
#include "FieldNames.h"
int   Delay = 100;

/****************************************************************************/
/*! Connects to the desired display. Returns the \c Display or \c 0 if
  no display could be obtained.

  \arg const char * DisplayName - name of the remote display.
  */
/****************************************************************************/
Display * remoteDisplay (const char * DisplayName) {

	int Event, Error;
	int Major, Minor;  

	// open the display
	Display * D = XOpenDisplay ( DisplayName );

	// did we get it?
	if ( ! D ) {
		// nope, so show error and abort
		fprintf (stderr, "could not open display \"%s\", aborting.\n",
				XDisplayName (DisplayName));
		exit ( EXIT_FAILURE );
	}

	// does the remote display have the Xtest-extension?
	if ( ! XTestQueryExtension (D, &Event, &Error, &Major, &Minor ) ) {
		// nope, extension not supported
		fprintf(stderr, "XTest extension not supported on server \"%s\"\n",DisplayString(D));

		// close the display and go away
		XCloseDisplay ( D );
		exit ( EXIT_FAILURE );
	}

	// print some information
	fprintf(stderr, "XTest for server \"%s\" is version %i.%i\n",DisplayString(D), Major,Minor);

	// execute requests even if server is grabbed 
	XTestGrabControl ( D, True ); 

	// sync the server
	XSync ( D,True ); 

	// return the display
	return D;
}

/****************************************************************************/
/*! Sends a \a character to the remote display \a RemoteDpy. The character is
  converted to a \c KeySym based on a character table and then reconverted to
  a \c KeyCode on the remote display. Seems to work quite ok, apart from
  something weird with the Alt key.

  \arg Display * RemoteDpy - used display.
  \arg char c - character to send.
  */
/****************************************************************************/
void sendChar(Display *RemoteDpy, char c)
{
	KeySym ks, sks, *kss, ksl, ksu;
	KeyCode kc, skc;
	int syms;

	sks=XK_Shift_L;

	ks=XStringToKeysym(chartbl[0][(unsigned char)c]);
	if ( ( kc = XKeysymToKeycode ( RemoteDpy, ks ) ) == 0 )
	{
		fprintf(stderr, "No keycode on remote display found for char: %c\n", c);
		
		return;
	}
	if ( ( skc = XKeysymToKeycode ( RemoteDpy, sks ) ) == 0 )
	{
		fprintf(stderr, "No keycode on remote display found for char: XK_Shift_L!\n");
		return;
	}

	kss=XGetKeyboardMapping(RemoteDpy, kc, 1, &syms);
	if (!kss)
	{
		fprintf(stderr, "XGetKeyboardMapping failed on the remote display (keycode: %i)\n", kc);
		return;
	}
	for (; syms && (!kss[syms-1]); syms--);
	if (!syms)
	{
		fprintf(stderr, "XGetKeyboardMapping failed on the remote display (no syms) (keycode: %i)\n", kc);
		XFree(kss);
		return;
	}
	XConvertCase(ks,&ksl,&ksu);
	if (ks==kss[0] && (ks==ksl && ks==ksu)) sks=NoSymbol;
	if (ks==ksl && ks!=ksu) sks=NoSymbol;
	if (sks!=NoSymbol) XTestFakeKeyEvent ( RemoteDpy, skc, True, Delay );
	XTestFakeKeyEvent ( RemoteDpy, kc, True, Delay );
	XFlush ( RemoteDpy );
	XTestFakeKeyEvent ( RemoteDpy, kc, False, Delay );
	if (sks!=NoSymbol) XTestFakeKeyEvent ( RemoteDpy, skc, False, Delay );
	XFlush ( RemoteDpy );
	XFree(kss);
}

/**
 * String splitting
 */

char ** string_split(char *path)
{
	char *ptr;
	char **retv = NULL;
	int items = 0;
	if(path == NULL)
		return NULL;

	ptr = strtok(path," ");
	while(ptr != NULL )
	{
		items++;
		/* make space */
		retv = realloc(retv,(items+1)*sizeof(char *));
		retv[items] = NULL;
		retv[items-1] = strdup(ptr);
		/* get next token */
		ptr = strtok(NULL, " ");
	}

	return retv;
}


void string_split_free(char **retv)
{
	int i=0;
	/* look all strings */
	for(i=0;retv[i] != NULL;i++)free(retv[i]);
	/* free the array */
	free(retv);
}

void xmacro_command(Display* RemoteDpy, int RemoteScreen, const char* ev)
{
	const char *str=NULL;
	int x, y;
	unsigned int b;
	int ks;
	int	kc;

        if (ev[0]=='#')
        {
                return;
        }
        if (!strncasecmp(DELAY,ev,strlen(DELAY)))
        {
                b = atoi(&ev[strlen(DELAY)+1]);
                usleep ( (int)(b*1000) );
        }
        else if (!strncasecmp(BUTTON_PRESS, ev,strlen(BUTTON_PRESS)))
        {
                b = atoi(&ev[strlen(BUTTON_PRESS)+1]);
                XTestFakeButtonEvent ( RemoteDpy, b, True, Delay );
        }
        else if (!strncasecmp(BUTTON_RELEASE,ev,strlen(BUTTON_RELEASE)))
        {
                b = atoi(&ev[strlen(BUTTON_RELEASE)+1]);
                XTestFakeButtonEvent ( RemoteDpy, b, False, Delay );
        }
        else if (!strncasecmp(MOTION_NOTIFY,ev, strlen(MOTION_NOTIFY)))
        {
                sscanf(ev,MOTION_NOTIFY" %i %i", &x, &y);
                XTestFakeMotionEvent ( RemoteDpy, RemoteScreen , x, y, Delay ); 
        }
        else if (!strncasecmp(KEY_CODE_PRESS,ev,strlen(KEY_CODE_PRESS)))
        {
                kc = atoi(&ev[strlen(KEY_CODE_PRESS)+1]);
                XTestFakeKeyEvent ( RemoteDpy, kc, True, Delay );
        }
        else if (!strncasecmp(KEY_CODE_RELEASE,ev,strlen(KEY_CODE_RELEASE)))
        {
                kc = atoi(&ev[strlen(KEY_CODE_RELEASE)+1]);
                XTestFakeKeyEvent ( RemoteDpy, kc, False, Delay );
        }
        else if (!strncmp(EXEC_BLOCK, ev, strlen(EXEC_BLOCK)))
        {
                char *script = strdup(&ev[strlen(EXEC_BLOCK)+1]);
                int pid;
                fprintf (stderr, "Exec '%s' blocking\n",script);			
                if ((pid=fork()) == 0)
                {
                        char **argv= string_split(script); 
                        execvp(argv[0], argv);
                        string_split_free(argv);
                        free(script);
                        exit(1);
                }
                /* Wait for execvp to be done */
                wait(NULL);
        }
        else if (!strncmp(EXEC_NO_BLOCK, ev, strlen(EXEC_NO_BLOCK)))
        {
                char *script = strdup(&ev[strlen(EXEC_NO_BLOCK)+1]);
                int pid;
                fprintf (stderr, "Exec '%s' non-blocking\n",script);			
                if ((pid=fork()) == 0)
                {
                        char **argv= string_split(script); 
                        execvp(argv[0], argv);
                        string_split_free(argv);
                        free(script);
                        exit(1);
                }
        }
        else if (!strncasecmp(KEY_SYM_PRESS,ev, strlen(KEY_SYM_PRESS)))
        {
                ks = atoi(&ev[strlen(KEY_SYM_PRESS)+1]);
                if ( ( kc = XKeysymToKeycode ( RemoteDpy, ks ) ) == 0 )
                {
                        return;
                }
                XTestFakeKeyEvent ( RemoteDpy, kc, True, Delay );
        }
        else if (!strncasecmp(KEY_SYM_RELEASE,ev,strlen(KEY_SYM_RELEASE)))
        {
                ks = atoi(&ev[strlen(KEY_SYM_RELEASE)+1]);
                if ( ( kc = XKeysymToKeycode ( RemoteDpy, ks ) ) == 0 )
                {
                        return;
                }
                XTestFakeKeyEvent ( RemoteDpy, kc, False, Delay );
        }
        else if (!strncasecmp(KEY_SYM,ev, strlen(KEY_SYM)))
        {
                ks = atoi(&ev[strlen(KEY_SYM)+1]);
                if ( ( kc = XKeysymToKeycode ( RemoteDpy, ks ) ) == 0 )
                {
                        fprintf(stderr, "No keycode on remote display found for keysym: %i",ks);
                        return;
                }
                XTestFakeKeyEvent ( RemoteDpy, kc, True, Delay );
                XFlush ( RemoteDpy );
                XTestFakeKeyEvent ( RemoteDpy, kc, False, Delay );
        }
        else if (!strncasecmp(KEY_STR_PRESS,ev,strlen(KEY_STR_PRESS)))
        {
                ks=XStringToKeysym(&(ev[strlen(KEY_STR_PRESS)+1]));
                if ( ( kc = XKeysymToKeycode ( RemoteDpy, ks ) ) == 0 )
                {
                        //	cerr << "No keycode on remote display found for '" << ev << "': " << ks << endl;
                        fprintf(stderr, "No keycode on remote display found for '%s':%i\n", ev, ks);
                        return;
                }
                XTestFakeKeyEvent ( RemoteDpy, (KeyCode)kc, True, Delay );
        }
        else if (!strncasecmp(KEY_STR_RELEASE,ev,strlen(KEY_STR_RELEASE)))
        {
                ks=XStringToKeysym(&(ev[strlen(KEY_STR_RELEASE)+1]));
                
                if ( ( kc = XKeysymToKeycode ( RemoteDpy, ks ) ) == 0 )
                {
                        fprintf(stderr, "No keycode on remote display found for '%s':%i\n", ev, ks);
                        return;
                }
                XTestFakeKeyEvent ( RemoteDpy, (KeyCode)kc, False, Delay );
        }
        else if (!strncasecmp(KEY_STR,ev,strlen(KEY_STR)))
        {
                ks=XStringToKeysym(&(ev[strlen(KEY_STR)+1]));
                if ( ( kc = XKeysymToKeycode ( RemoteDpy, ks ) ) == 0 )
                {
                        fprintf(stderr, "No keycode on remote display found for '%s':%i\n", ev, ks);
                        return;
                }
                XTestFakeKeyEvent ( RemoteDpy, kc, True, Delay );
                XFlush ( RemoteDpy );
                XTestFakeKeyEvent ( RemoteDpy, kc, False, Delay );
        }
        else if (!strncasecmp(STRING,ev,strlen(STRING)))
        {
                str = &(ev[strlen(STRING)+1]);
                b=0;
                while(str[b]) sendChar(RemoteDpy, str[b++]);
        }
        else{
                fprintf(stderr, "error: %s\n", ev);
        }
        
        // sync the remote server
        XSync ( RemoteDpy, False );
}
