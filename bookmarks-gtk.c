#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bookmarks-gtk.h"

/* This is a callback function. The data arguments are ignored
 * in this example. More on callbacks below. */
static void zir(GtkWidget *widget, gpointer data) {
	
	char *array[4] = {"/usr/bin/google-chrome", "", data, NULL};			// TODO Use from *.h to determine appropriate command for each button
	
	g_spawn_async(NULL, array, NULL, 4, NULL, NULL, NULL, NULL);
}

static gboolean delete_event(GtkWidget *widget, GdkEvent *event, gpointer data) {
	
	gtk_main_quit ();
	return FALSE;
}

int main(int argc, char *argv[]) {
	
	// TEST //
	GtkWidget *button;
	GtkWidget *quitbox;
	//////////
	
	// Creating Widgets //
	GtkWidget *mainWindow;
	GtkWidget *mainColumn;
	GtkWidget *mainLabel;
	
	GtkWidget *mainRow;
	GtkWidget *frame[FRAMES];
	GtkWidget *sectionBox;

	gtk_init (&argc, &argv);	

	// Creating mainWindow //
	mainWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title (GTK_WINDOW (mainWindow), mainWindow_title);
	gtk_window_set_resizable (GTK_WINDOW (mainWindow), mainWindow_isResizable);
	gtk_window_set_keep_above(GTK_WINDOW (mainWindow), mainWindow_keepAboveOtherWindows);
	gtk_window_set_default_size(GTK_WINDOW (mainWindow), mainWindow_width, mainWindow_height);
	gtk_window_move(GTK_WINDOW (mainWindow), mainWindow_horizontalPosition, mainWindow_verticalPosition);
											
	// Settings for redirecting GTK Signals //										
	g_signal_connect (mainWindow, "delete-event", G_CALLBACK (delete_event), NULL);
	g_signal_connect (mainWindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	
	// Creating mainColumn box to fit the mainLabel on top, then the frames, then the quit button // 
	mainColumn = gtk_vbox_new (FALSE, 0);
	
	// Creating the mainLabel //
	mainLabel = gtk_label_new (NULL);
	gtk_label_set_justify(GTK_LABEL (mainLabel), mainLabel_justifyType);
	gtk_label_set_markup (GTK_LABEL (mainLabel), g_markup_printf_escaped ("<span face=\"%s\" size=\"%s\" font_weight=\"%s\">%s</span>", mainLabel_fontFamily, mainLabel_fontSize, mainLabel_fontWeight, mainLabel_string));
	gtk_box_pack_start (GTK_BOX (mainColumn), mainLabel, FALSE, FALSE, 0);
	gtk_widget_show (mainLabel);
	
	// Creating mainRow box to fit the frames of each section //
	mainRow = gtk_hbox_new (FALSE, 0);
	
	for (int currentFrame = 0; currentFrame < FRAMES; currentFrame++) {
		
		frame[currentFrame] = gtk_frame_new(frames_string[currentFrame]);
		gtk_frame_set_label_align(GTK_FRAME (frame[currentFrame]), frames_horizontalAlign, frames_verticalAlign);
		gtk_frame_set_shadow_type (GTK_FRAME (frame[currentFrame]), frames_shadowType);
		
		sectionBox = gtk_vbox_new (FALSE, 0);
		
		for (int currentBookmark = 0; currentBookmark < MAX_BOOKMARKS; currentBookmark++) {
			
			if (bookmarks[currentBookmark][0] == NULL)
				break;
			
			if (strcmp(frames_string[currentFrame], bookmarks[currentBookmark][0]) == 0) {
				
				button = gtk_button_new_with_label(bookmarks[currentBookmark][1]);
				g_signal_connect(button, "clicked", G_CALLBACK (zir), bookmarks[currentBookmark][3]);
				gtk_box_pack_start(GTK_BOX (sectionBox), button, TRUE, TRUE, 0);
				gtk_widget_show(button);
				
			}
		}
		
		gtk_container_add(GTK_CONTAINER (frame[currentFrame]), sectionBox);
		gtk_widget_show(sectionBox);
		
		gtk_box_pack_start (GTK_BOX (mainRow), frame[currentFrame], TRUE, TRUE, frames_padding);
		gtk_widget_show(frame[currentFrame]);
		
	}
	
	gtk_box_pack_start (GTK_BOX (mainColumn), mainRow, FALSE, FALSE, 0);
	gtk_widget_show (mainRow);
	
	// TEST //
	/* Args are: homogeneous, spacing, expand, fill, padding */
	//box2 = make_box (TRUE, 0, TRUE, TRUE, 0);
	//gtk_box_pack_start (GTK_BOX (mainColumn), box2, FALSE, FALSE, 0);
	//gtk_widget_show (box2);
	
	/* Another new separator. */
	//separator = gtk_hseparator_new ();
	/* The last 3 arguments to gtk_box_pack_start are:
	 * expand, fill, padding. */
	//gtk_box_pack_start (GTK_BOX (mainColumn), separator, FALSE, TRUE, 5);
	//gtk_widget_show (separator);

	
	/* Create another new hbox.. remember we can use as many as we need! */
	quitbox = gtk_hbox_new (FALSE, 0);
	
	/* Our quit button. */
	button = gtk_button_new_with_label ("Quit");
	
	 /* Setup the signal to terminate the program when the button is clicked */
	g_signal_connect_swapped (button, "clicked",
			      G_CALLBACK (gtk_main_quit),
			      mainWindow);
	/* Pack the button into the quitbox.
	* The last 3 arguments to gtk_box_pack_start are:
	* expand, fill, padding. */
	gtk_box_pack_start (GTK_BOX (quitbox), button, TRUE, FALSE, 0);
	/* pack the quitbox into the vbox (mainColumn) */
	gtk_box_pack_start (GTK_BOX (mainColumn), quitbox, FALSE, FALSE, 0);
    
	/* Pack the vbox (mainColumn) which now contains all our widgets, into the
	* main window. */
	gtk_container_add (GTK_CONTAINER (mainWindow), mainColumn);

	/* And show everything left */
	gtk_widget_show (button);
	gtk_widget_show (quitbox);

	gtk_widget_show (mainColumn);

	
	/*
	for (int i = 0; i < COLUMNS; i++) {
	
		columns[i] = gtk_vbox_new(FALSE, 0);
		gtk_container_add (GTK_CONTAINER (window), columns[i]);
		
		
		// Sets a TITLE for each column with settings //
		titles[i] = gtk_label_new("TITLE");					// TODO Replace TITLE with something from *.h
		gtk_label_set_justify(GTK_LABEL (titles[i]), GTK_JUSTIFY_LEFT);		// TODO Replace with something from *.h			
		gtk_label_set_line_wrap(GTK_LABEL (titles[i]), TRUE);			// TODO Replace with something from *.h
		
		
		gtk_widget_show(titles[i]);
		gtk_widget_show(columns[i]);
		
	}
	*/
	
	//bookmarks = gtk_vbox_new (FALSE, 0);						// TODO Depreciate All
	//gtk_container_add (GTK_CONTAINER (window), bookmarks);
	//
	//for (int i = 0; i < NUM; i++) {
	//	
	//	button[i] = gtk_button_new_with_label(buttonData[i][0]);
	//	g_signal_connect (button[i], "clicked", G_CALLBACK (zir), buttonData[i][2]);
	//	gtk_box_pack_start (GTK_BOX(bookmarks), button[i], FALSE, FALSE, 0);
	//	gtk_widget_show (button[i]);
	//	
	//}
	//gtk_widget_show (bookmarks);

	gtk_widget_show (mainWindow);
	gtk_main ();
	
	return 0;
}
