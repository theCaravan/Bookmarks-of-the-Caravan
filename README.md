# Bookmarks-of-the-Caravan
This is a program that has buttons allowing the user to click on a button and it will 
open Google Chrome to the links the buttons were mapped to.  

This program can only run in Linux with Google Chrome and GTK+. Without any of this would constitute undefined behavior.

First, type on the terminal (replace DOWNLOAD_LOCATION with where the folder was extracted to):

cd DOWNLOAD_LOCATION

make

You should see a program called bookmarks-gtk (without any extension or .xxx).

Second, Type on the terminal (the & is to ensure that it runs on the background):

./bookmarks-gtk &

You should see a window and you will be able to interact with the program.

=============================

Editing:

Edit the file bookmarks-gtk.h. There are a lot of options to change so you can change font sizes.

Before adding a bookmark, check the *frames_string[FRAMES], which holds sections.

Once you have finished with that, add a bookmark by copying the following (do note that if you are adding a bookmark to the very end, remove the comma or else errors would apprear):

{"", "", "/usr/bin/google-chrome", ""}, 

The first string is the section name, which you choose from *frames_string[FRAMES]. Not choosing a section from this list would cause undefined behavior. 

The second string is the button label. 

The third string is the path of Google Chrome. I have had issues mapping this to a different program but you are free to tinker with it.

The final string is the URL.

Done!

Any problems or bugs should be reported to sb5060tx@gmail.com. My inbox is mainly empty, so do not shy away from shooting me an email about a bug or problem with the program.
