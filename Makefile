all: bookmarks-gtk

unstable: bookmarks-gtk-unstable

bookmarks-gtk: 
	gcc -Wall bookmarks-gtk.c -std=c11 -o bookmarks-gtk `pkg-config --cflags --libs gtk+-2.0`

bookmarks-gtk-unstable: 
	gcc -Wall bookmarks-gtk.c -ggdb -std=c11 -o bookmarks-gtk-unstable `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm -rf bookmarks-gtk bookmarks-unstable

clean-stable:
	rm -rf bookmarks-gtk

clean-unstable:
	rm -rf bookmarks-gtk-unstable
