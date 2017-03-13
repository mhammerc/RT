#include "rt.h"
#include <gtk/gtk.h>

int			main(int argc, char **argv)
{
	static GtkApplication	*app;
	int						status;

	//gdk_threads_init();
	app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(build_interface), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return (status);
}
