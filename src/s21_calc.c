// #include "s21_calc.h"
#include <gtk/gtk.h>
#include "s21_pars.h"

static void printChars(GtkWidget *button, gpointer data)
{
    const char* str = gtk_button_get_label(GTK_BUTTON(button));
    GtkEntryBuffer* buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    gtk_entry_buffer_insert_text(GTK_ENTRY_BUFFER(buffer), gtk_entry_buffer_get_length(GTK_ENTRY_BUFFER(buffer)), str, -1);

}

static void cleanTextBox(GtkWidget *button, gpointer data) {
    GtkEntryBuffer* buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    gtk_entry_buffer_set_text(GTK_ENTRY_BUFFER(buffer), "", -1);
}

static void Result(GtkWidget *button, gpointer data) {
    GtkEntryBuffer* buffer = gtk_entry_get_buffer(GTK_ENTRY(data));
    char *elem = (char*)gtk_entry_buffer_get_text(GTK_ENTRY_BUFFER(buffer));
    double res = mainFunc(elem);
    cleanTextBox(button, data);
    char* result = (char*)malloc(1024*sizeof(char));
    snprintf(result, sizeof(result), "%lf", res);
    gtk_entry_buffer_insert_text(GTK_ENTRY_BUFFER(buffer), gtk_entry_buffer_get_length(GTK_ENTRY_BUFFER(buffer)), result, -1);
    free(result);
}

static void activate (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *button;
  GtkWidget *entry;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");

  grid = gtk_grid_new();
  gtk_window_set_child (GTK_WINDOW (window), grid);

  entry = gtk_entry_new ();
  gtk_grid_attach (GTK_GRID (grid), entry, 0, 0, 7, 1);



  button = gtk_button_new_with_label ("(");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 1, 1, 1);

  button = gtk_button_new_with_label (".");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 1, 1, 1, 1);

  button = gtk_button_new_with_label (")");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 2, 1, 1, 1);

  button = gtk_button_new_with_label ("x");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 3, 1, 1, 1);

  button = gtk_button_new_with_label ("asin");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 4, 1, 1, 1);

  button = gtk_button_new_with_label ("atan");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 5, 1, 1, 1);




  button = gtk_button_new_with_label ("7");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 2, 1, 1);

  button = gtk_button_new_with_label ("8");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 1, 2, 1, 1);

  button = gtk_button_new_with_label ("9");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 2, 2, 1, 1);

  button = gtk_button_new_with_label ("/");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 3, 2, 1, 1);

  button = gtk_button_new_with_label ("%");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 4, 2, 1, 1);

  button = gtk_button_new_with_label ("sin");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 5, 2, 1, 1);



  button = gtk_button_new_with_label ("4");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 3, 1, 1);

  button = gtk_button_new_with_label ("5");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 1, 3, 1, 1);

  button = gtk_button_new_with_label ("6");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 2, 3, 1, 1);

  button = gtk_button_new_with_label ("*");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 3, 3, 1, 1);

  button = gtk_button_new_with_label ("log");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 4, 3, 1, 1);

  button = gtk_button_new_with_label ("cos");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 5, 3, 1, 1);

  button = gtk_button_new_with_label ("=");
  g_signal_connect (button, "clicked", G_CALLBACK (Result), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 6, 1, 1, 5);




  button = gtk_button_new_with_label ("1");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 4, 1, 1);

  button = gtk_button_new_with_label ("2");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 1, 4, 1, 1);

  button = gtk_button_new_with_label ("3");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 2, 4, 1, 1);

  button = gtk_button_new_with_label ("-");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 3, 4, 1, 1);

  button = gtk_button_new_with_label ("ln");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 4, 4, 1, 1);


  button = gtk_button_new_with_label ("tan");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 5, 4, 1, 1);


  
  

  button = gtk_button_new_with_label ("0");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 0, 5, 1, 1);

  button = gtk_button_new_with_label ("AC");
  g_signal_connect (button, "clicked", G_CALLBACK (cleanTextBox), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 1, 5, 2, 3);

  button = gtk_button_new_with_label ("+");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 3, 5, 1, 1);
 
  button = gtk_button_new_with_label ("sqrt");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 4, 5, 1, 1);

  button = gtk_button_new_with_label ("acos");
  g_signal_connect (button, "clicked", G_CALLBACK (printChars), entry);
  gtk_grid_attach (GTK_GRID (grid), button, 5, 5, 1, 1);

  gtk_widget_show (window);
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int status;
  app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);
  return status;
}


