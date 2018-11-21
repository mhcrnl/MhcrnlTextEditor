#include <stdlib.h>
#include <gtk/gtk.h>

const gchar *title = "MhcrnlTextEditor";
const gchar *author = "Mihai Cornel mhcrnl@gmail.com";
const gchar *version = "0.01";
/*
    1.Widget for open-dialog
*/
typedef struct _OpenDialog{
  GtkWidget *window;
  GtkTextBuffer *buffer;
  gchar *filename;
} OpenDialog;
/*
    1.Function invoked when open menu item is clicked
*/
void open_dialog_selected(GtkWidget *widget, OpenDialog *odlog){

  GtkWidget *dialog;

  dialog = gtk_file_chooser_dialog_new ("Open File",
    GTK_WINDOW(odlog->window),
    GTK_FILE_CHOOSER_ACTION_OPEN,
    GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
    GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
    NULL);

  if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)
  {
   gchar *filename;
   gchar *contents;
   filename = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
   g_file_get_contents(filename, &contents, NULL, NULL);
   gtk_text_buffer_set_text(odlog->buffer, contents, -1);
   gtk_window_set_title(GTK_WINDOW(odlog->window), filename);
   odlog->filename=filename;
   g_free (filename);
 }
 gtk_widget_destroy(dialog);
}
/*
    About
*/
void show_about(GtkWidget *widget, gpointer data)
{
   GtkWidget *dialog;
   dialog = gtk_message_dialog_new(GTK_WINDOW(data),
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_INFO,
                GTK_BUTTONS_OK,
                title);
    gtk_window_set_title(GTK_WINDOW(dialog), title);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void helloWorld (GtkWidget *wid, GtkWidget *win) {
    GtkWidget *dialog = NULL;

    dialog = gtk_message_dialog_new (GTK_WINDOW (win), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Hello World!");
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_dialog_run (GTK_DIALOG (dialog));
    gtk_widget_destroy (dialog);
}

int main (int argc, char *argv[]) {
    //GtkWidget *button = NULL;
    GtkWidget *win = NULL;
    GtkWidget *vbox = NULL;
    /*
        Create text view: https://developer.gnome.org/gtk2/stable/GtkTextView.html
    */
    GtkWidget *text_view = NULL;
    GtkTextBuffer *buffer = NULL;
    /*
        Create menu
    */
    GtkWidget *menubar;
    GtkWidget *fileMenu;

    GtkWidget *fileMi;
    GtkWidget *quitMi;
    GtkWidget *openMi;

    GtkWidget *helpMenu;
    GtkWidget *helpMi;
    /*
        Initialize GTK+
    */
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    gtk_init (&argc, &argv);
    g_log_set_handler ("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);
    /*
     Create the main window
     */
    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width (GTK_CONTAINER (win), 8);
    gtk_window_set_title (GTK_WINDOW (win), "MhcrnlTextEditor");
    gtk_window_set_position (GTK_WINDOW (win), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(win), 800, 600);
    gtk_widget_realize (win);
    g_signal_connect (win, "destroy", gtk_main_quit, NULL);

    /* Create a vertical box with buttons */
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (win), vbox);

    text_view = gtk_text_view_new();
    gtk_container_add(GTK_CONTAINER(vbox), text_view);
    /*
        Initializing open dialog
    */
    OpenDialog odlog;
    odlog.window = win;
    odlog.buffer= buffer;

    menubar = gtk_menu_bar_new();
    fileMenu = gtk_menu_new();
    helpMenu = gtk_menu_new();

    fileMi = gtk_menu_item_new_with_label("File");
    openMi = gtk_menu_item_new_with_label("Open");
    quitMi = gtk_menu_item_new_with_label("Quit");

    helpMi = gtk_menu_item_new_with_label("Help");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), fileMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), openMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu), quitMi);

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(helpMi), helpMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(helpMenu), helpMi);

    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
    //gtk_menu_shell_append(GTK_MENU_SHELL(menubar), helpMi);
    //button = gtk_button_new_from_stock (GTK_STOCK_DIALOG_INFO);
    //g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (helloWorld), (gpointer) win);
    gtk_box_pack_start (GTK_BOX (vbox), menubar, FALSE, FALSE, 0);

    //button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect (G_OBJECT(quitMi), "activate",
                      G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect (G_OBJECT(openMi), "activate",
                      G_CALLBACK(show_about), win);
    //gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);

    /* Enter the main loop */
    gtk_widget_show_all (win);
    gtk_main ();
    return 0;
}
