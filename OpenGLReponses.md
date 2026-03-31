1. objectives 
- get you familiar with the OpenGL libraries and learn the rendering pipeline of the library.
- 
Answers
1)
-  the solid version of the teapot
- depth buffering,coloring faces accordingly?
2)
- radius > 1.0 goes over the window
- more slices
- stacks lil circles from top down view
- more slices + more stacks gives more faces to rasterize
3)
- fovy the bigger the more the object is further than the camera 0-180 : we zoom out , 1 is the biggest then we zoom out until we cant see it at 180
- 180-360the inverse 
- when increasing zNear the object starts to fade away when it reaches more than 2.1 before completely disappearing after 3.4
4) 1-    camera basis breaks up must not be parallel to (center - eye) so the product is not 0.
2- // position a
      //gluLookAt(0.0,2.0,0.0,0.0,0.0,0.0,1.0,0.0,0);
      //position b
      gluLookAt(0.0,.0,-2,0.0,0.0,0,1.0,1.0,0);
we change the up vector to have the right orientation/ro ll for position  (a)
screen rotated (rolled) so top points toward world +X ( right on screen)
   (
   // up = (1,0,0) means the top of the screen is world +X,
   // so the view is rolled compared to the usual up=(0,0,1).

// Position B:
// up = (1,1,0) gives a diagonal screen-top direction (between +X and +Y),
// i.e. an additional roll)
(++glutWireTeapot(...) uses whatever matrix is on top at that exact line.)
5) 
   After a repaint event (resize, uncovering the window, etc.), objects start to drift/rotate/scale more and more, or the composition “accumulates” wrongly over time.
   That second glPopMatrix() is supposed to restore the ModelView matrix to what it was before the corresponding glPushMatrix().
The stack becomes unbalanced: you push, you modify (translate/rotate/scale), but you never pop.
On each new call to display, you start from a ModelView state that is not the expected baseline 
Over multiple repaints, transformations effectively compound, because you are no longer returning to the same “camera/object base transform” each frame.
6) When you move gluLookAt(...) after the 2nd glPushMatrix() in display(), the view (camera) matrix gets applied only inside that pushed matrix scope instead of being the global baseline for the whole frame.
The camera transform becomes local to that block / that teapot, not to the whole scene.
After you glPopMatrix(), you restore the previous matrix without the gluLookAt, so later draws (e.g., your 3rd blue teapot) are rendered with the wrong ModelView (often identity or a different transform), meaning it can end up behind the camera / out of the frustum and “disappear”.
 
7)If you move glLoadIdentity() from main to just before “draw scene” in display(), then every repaint resets the ModelView matrix to identity right before drawing.
The viewing transform you previously set in main (e.g. gluLookAt) gets wiped out at the start of each display().
Your teapots are then drawn with the wrong camera (default view), so the blue 3rd teapot can end up outside the view volume / behind the camera and “disappear”.
Why (stack reasoning): glLoadIdentity() changes the current ModelView matrix at the top of the stack. Doing it in display() resets the baseline for the whole frame unless you apply gluLookAt again after that reset (and before any modeling transforms).