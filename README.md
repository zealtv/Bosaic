# Bosaic
A live capture, meta-image mosaic application written in openFrameworks

Written of OSX using openFrameworks 0.8.4
Tested on Yosemite



The app is suited to a portrait display @ 1080x1920
Press 'f' to go fullscreen


//Capturing images
//--------------------------------------
press space bar to preview the webcam
press space bar again to capture an image or press escape to cancel

It will hunt for the second webcam available - ie not the inbuilt webcam
this webcam will be captured at 1080x1920 and should be physically rotated by 90 degrees


images will be stored in the data/captures folder
You can preload this folder with images (png or jpg) and they will be loaded at startup.
For best results the images should be 1080x1920 or atleast 9:16 aspect.
If no images are present, the larger portrait image will be used in place of them.
