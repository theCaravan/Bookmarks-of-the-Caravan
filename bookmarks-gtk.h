#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define NUM 54	// TODO Depreciate
#define FRAMES 7

#define MAX_BOOKMARKS 100
#define MAX_FRAMES 100

// Settings for mainWindow //
const gchar *mainWindow_title 			= "TheCaravan Bookmarks";
gboolean mainWindow_isResizable 		= TRUE;
gboolean mainWindow_keepAboveOtherWindows 	= TRUE;
gint mainWindow_width 				= 430;
gint mainWindow_height 				= 420;
gint mainWindow_horizontalPosition 		= 0;
gint mainWindow_verticalPosition 		= 0;

// Settings for mainLabel //
const gchar *mainLabel_string 			= "Bookmarks of the Caravan";
const gchar *mainLabel_fontFamily 		= "Garamond";
const gchar *mainLabel_fontSize 		= "xx-large";
const gchar *mainLabel_fontWeight 		= "bold";
GtkJustification mainLabel_justifyType 		= GTK_JUSTIFY_CENTER;

// Settings for frames //
const gchar *frames_string[FRAMES] 		= {"Outside World", "INET 4051", "INET 4083", "U of M", "2018", "Maps and Metro", "Miscellaneous"};
gfloat frames_horizontalAlign			= 0.0;
gfloat frames_verticalAlign			= 0.0;
guint frames_padding				= 3;
GtkShadowType frames_shadowType			= GTK_SHADOW_OUT;


// Bookmarks //
char *bookmarks[MAX_BOOKMARKS][4] = {

	/* 01 */	{"Outside World",	"Hotmail", 			"/usr/bin/google-chrome",		"https://outlook.live.com/owa/"},
	/* 02 */	{"Outside World",	"Personal Gmail", 		"/usr/bin/google-chrome",		"https://mail.google.com/mail/u/0/"},
	/* 03 */	{"Outside World",	"U of M Gmail", 		"/usr/bin/google-chrome",		"https://mail.google.com/mail/u/1/"},
	/* 04 */	{"Outside World",	"Google Hangouts", 		"/usr/bin/google-chrome",		"https://hangouts.google.com/"},
	/* 05 */	{"Outside World",	"Work Income",			"/usr/bin/google-chrome",		"https://1drv.ms/x/s!Ar23fzKhY4HqiMEe3V9OpYJCWVz0Mw"},
	/* 06 */	{"Outside World",	"Amazon Cart",			"/usr/bin/google-chrome",		"https://www.amazon.com/gp/cart/view.html/ref=nav_cart"},
	/* 07 */	{"Outside World",	"LinkedIn", 			"/usr/bin/google-chrome",		"http://www.linkedin.com"},
	/* 08 */	{"Outside World",	"OneDrive", 			"/usr/bin/google-chrome",		"onedrive.live.com"},
	/* 09 */	{"Outside World",	"Personal Google Drive", 	"/usr/bin/google-chrome",		"https://drive.google.com/drive/u/0/"},
	/* 10 */	{"Outside World",	"UMN Google Drive", 		"/usr/bin/google-chrome",		"https://drive.google.com/drive/u/1/"},
	/* 11 */	{"Outside World",	"Personal Google Calendar",	"/usr/bin/google-chrome",		"https://calendar.google.com/calendar/render?tab=mc#main_7"},
	/* 12 */	{"Outside World",	"U of M Google Calendar",	"/usr/bin/google-chrome",		"https://calendar.google.com/calendar/b/1/render?tab=mc#main_7"},
	/* 13 */	{"Outside World",	"Feedly",			"/usr/bin/google-chrome",		"http://feedly.com/i/latest"},
	/* 14 */	{"Outside World",	"Pocket",			"/usr/bin/google-chrome",		"https://getpocket.com/a/queue/"},
	/* 15 */	{"Outside World",	"YouTube",			"/usr/bin/google-chrome",		"https://www.youtube.com/"},
	/* 16 */	{"Outside World",	"Netflix",			"/usr/bin/google-chrome",		"https://www.netflix.com/"},
	/* 17 */	{"Outside World",	"Hulu",				"/usr/bin/google-chrome",		"https://www.hulu.com/"},
	/* 18 */	{"INET 4051",		"Canvas",			"/usr/bin/google-chrome",		"https://canvas.umn.edu/courses/33650"},
	/* 19 */	{"INET 4051",		"Canvas Grades",		"/usr/bin/google-chrome",		"https://canvas.umn.edu/courses/33650/grades"},
	/* 20 */	{"INET 4051",		"Excel Grades",			"/usr/bin/google-chrome",		"https://1drv.ms/x/s!Ar23fzKhY4HqiM8F9OGkU2jbMvCwRA"},
	/* 21 */	{"INET 4083",		"Canvas",			"/usr/bin/google-chrome",		"https://canvas.umn.edu/courses/49133"},
	/* 22 */	{"INET 4083",		"Canvas Grades",		"/usr/bin/google-chrome",		"https://canvas.umn.edu/courses/49133/grades"},
	/* 23 */	{"INET 4083",		"Excel Grades",			"/usr/bin/google-chrome",		"https://1drv.ms/x/s!Ar23fzKhY4HqiM8E96wtq6EPrS-LhA"},
	/* 24 */	{"U of M",		"Canvas Home",			"/usr/bin/google-chrome",		"canvas.umn.edu"},
	/* 25 */	{"U of M",		"MyU",				"/usr/bin/google-chrome",		"myu.umn.edu"},
	/* 26 */	{"U of M",		"Classroom Search",		"/usr/bin/google-chrome",		"http://www.classroom.umn.edu/roomsearch/"},
	/* 27 */	{"U of M",		"Astra",			"/usr/bin/google-chrome",		"https://www.aaiscloud.com/UMN/Calendars/GuestDailyGridCalendar.aspx?calendarId=4f0cc5c0-2763-11e5-8b40-e7d4b03363e9&isDay=true"},
	/* 28 */	{"U of M",		"IT UMN Status",		"/usr/bin/google-chrome",		"https://umnprd.service-now.com/sysstatus/"},
	/* 29 */	{"U of M",		"CSE Print Quota",		"/usr/bin/google-chrome",		"https://winprint.cs.umn.edu:9192/app"},
	/* 30 */	{"U of M",		"AMCC UMN",			"/usr/bin/google-chrome",		"https://amccumn.com/"},
	/* 31 */	{"U of M",		"MSA UMN",			"/usr/bin/google-chrome",		"http://www.msaumn.org/"},
	/* 32 */	{"2018",		"GradPlanner",			"/usr/bin/google-chrome",		"https://onestop2.umn.edu/gradplanner/Initialize.do?campus=UMNTC"},
	/* 33 */	{"2018",		"Schedule Builder",		"/usr/bin/google-chrome",		"https://schedulebuilder.umn.edu/"},
	/* 34 */	{"2018",		"ITI Catalog",			"/usr/bin/google-chrome",		"https://onestop2.umn.edu/pcas/viewCatalogProgram.do?programID=163"},
	/* 35 */	{"2018",		"APAS",				"/usr/bin/google-chrome",		"https://onestop2.umn.edu/darwin/login.jsp"},
	/* 36 */	{"2018",		"ITI CCE",			"/usr/bin/google-chrome",		"http://cce.umn.edu/information-technology-infrastructure-major"},
	/* 37 */	{"Maps and Metro",	"Google Maps",			"/usr/bin/google-chrome",		"https://www.google.com/maps"},
	/* 38 */	{"Maps and Metro",	"Metro Transit",		"/usr/bin/google-chrome",		"https://www.metrotransit.org/"},
	/* 42 */	{"Maps and Metro",	"Rider Alerts",			"/usr/bin/google-chrome",		"https://www.metrotransit.org/rider-alerts"},
	/* 43 */	{"Maps and Metro",	"Green Eastbound - East Bank",	"/usr/bin/google-chrome",		"https://www.metrotransit.org/NexTripBadge.aspx?route=902&direction=2&stop=EABK"},
	/* 44 */	{"Maps and Metro",	"Green Westbound - East Bank",	"/usr/bin/google-chrome",		"https://www.metrotransit.org/NexTripBadge.aspx?route=902&direction=3&stop=EABK"},
	/* 45 */	{"Maps and Metro",	"Bus 2 Eastbound - Anderson",	"/usr/bin/google-chrome",		"https://www.metrotransit.org/NexTripBadge.aspx?route=2&direction=2&stop=ANHA"},
	/* 46 */	{"Miscellaneous",	"OneDrive Home",		"/usr/bin/google-chrome",		"onedrive.live.com"},
	/* 47 */	{"Miscellaneous",	"Google Keep",			"/usr/bin/google-chrome",		"https://keep.google.com/u/0/"},
	/* 48 */	{"Miscellaneous",	"Money Excel",			"/usr/bin/google-chrome",		"https://1drv.ms/x/s!Ar23fzKhY4HqhfI4sZN3ze1FJtCD3w"},
	/* 49 */	{"Miscellaneous",	"Transcript Excel",		"/usr/bin/google-chrome",		"https://1drv.ms/x/s!Ar23fzKhY4HqhJoE5xkl57-ldvHPqw"},
	/* 50 */	{"Miscellaneous",	"Al-Amal School",		"/usr/bin/google-chrome",		"http://www.al-amal.org/"},
	/* 51 */	{"Miscellaneous",	"DistroWatch",			"/usr/bin/google-chrome",		"http://distrowatch.com/"},
	/* 52 */	{"Miscellaneous",	"MyBoynton",			"/usr/bin/google-chrome",		"https://myboynton.bhs.umn.edu/home.aspx"},
	/* 53 */	{"Miscellaneous",	"UMN Jobs",			"/usr/bin/google-chrome",		"https://humanresources.umn.edu/jobs"}

};

char *linkToCommand[2][2] = {

	/* 01 */	{"/usr/bin/google-chrome",	"--window-position=9999,0"},
	/* 02 */	{"/usr/bin/gedit",		""}

};

