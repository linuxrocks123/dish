/*
 * Dump the accessibility hierarchy tree for a given application.
 * It shows the (name, role) for each object
 * TODO: show stateset too.
 *
 * To get the name it tries get_name and the labelled_by relationship.
 *
 */

#include <atspi/atspi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static gchar*
get_label(AtspiAccessible *accessible)
{
  GArray *relations;
  AtspiRelation *relation;
  gint i;
  gchar *result = "";

  relations = atspi_accessible_get_relation_set (accessible, NULL);
  if (relations == NULL) {
    return "";
  }

  for (i = 0; i < relations->len; i++) {
    relation = g_array_index (relations, AtspiRelation*, i);

    if (atspi_relation_get_relation_type (relation) == ATSPI_RELATION_LABELLED_BY) {
      result = atspi_accessible_get_name (atspi_relation_get_target (relation, 0), NULL);
    }
  }

  if (relations != NULL)
    g_array_free (relations, TRUE);

  return result;
}

static void output_atkocr_line(int x, int w, int y, int h, const char* text)
{
  if(!*text || x < 0 || y < 0)
    return;
  
  typedef struct Duplicate_Suppression
  {
    int x, w, y, h;
    char text[16];
  } Duplicate_Suppression;

  static Duplicate_Suppression* duplicate_list;
  static unsigned duplicate_list_size;

  Duplicate_Suppression current = {x, w, y, h};
  strncpy(current.text,text,15);

  for(unsigned i=0; i<duplicate_list_size; i++)
    if(!memcmp(duplicate_list + i, &current, sizeof(Duplicate_Suppression)))
      return;

  duplicate_list_size++;
  duplicate_list = realloc(duplicate_list, sizeof(Duplicate_Suppression) * duplicate_list_size);
  memcpy(duplicate_list + duplicate_list_size - 1, &current, sizeof(Duplicate_Suppression));

  printf("atkocr INFO: [[[%d, %d], [%d, %d], [%d, %d], [%d, %d]], (\"", x, y, x+w, y, x+w, y+h, x, y+h);
  while(*text)
  {
    if(*text=='"')
      putchar('\\');
    putchar(*text);
    text++;
  }

  puts("\", 1)]");
}

static gchar*
print_info (AtspiAccessible *accessible)
{
  gchar *name = "";
  gchar *role_name = "";
  gchar* text = "";
  AtspiPoint* position = NULL;
  AtspiPoint* size = NULL;

  if (accessible != NULL) {
    name = atspi_accessible_get_name (accessible, NULL);
    if ((name == NULL) || (g_strcmp0 (name, "") == 0))
        name = get_label (accessible);

    role_name = atspi_accessible_get_role_name (accessible, NULL);
    
    AtspiText* text_subobject = atspi_accessible_get_text(accessible);
    if(text_subobject)
      text = atspi_text_get_text(text_subobject,0,100,NULL);
    
    AtspiComponent* component_subobject = atspi_accessible_get_component(accessible);
    if(component_subobject)
    {
      position = atspi_component_get_position(component_subobject,ATSPI_COORD_TYPE_SCREEN,NULL);
      size = atspi_component_get_size(component_subobject,NULL);
    }
  }

  if(position && size)
  {
    output_atkocr_line(position->x, size->x, position->y, size->y, name);
    output_atkocr_line(position->x, size->x, position->y, size->y, role_name);
    output_atkocr_line(position->x, size->x, position->y, size->y, text);
  }
  return NULL;
}

static void
dump_node_content (AtspiAccessible *node)
{
  AtspiAccessible *inner_node = NULL;
  gint c;
  gchar *string = NULL;

  print_info(node);

  for (c = 0; c < atspi_accessible_get_child_count (node, NULL); c++) {
    inner_node = atspi_accessible_get_child_at_index (node, c, NULL);
    dump_node_content (inner_node);
    g_object_unref (inner_node);
  }

  g_free (string);
}

int main()
{
  gint i;
  AtspiAccessible *desktop = NULL;
  AtspiAccessible *app = NULL;

  atspi_init ();

  desktop = atspi_get_desktop (0);
  for (i = 0; i < atspi_accessible_get_child_count (desktop, NULL); i++) {
    app = atspi_accessible_get_child_at_index (desktop, i, NULL);
    dump_node_content (app);
    g_object_unref (app);
  }

  return 1;
}
