GET MORE INFORMATION AT:

https://helmutduregger.wordpress.com/2011/11/21/simulation-of-large-and-dense-crowds-on-the-gpu-using-opencl/


HOW TO BUILD:

Builds easily with Eclipse CDT and the Qt plugin.

To change between configurations right click on the project in Eclipse's
Project Explorer and select
 
    C/C++ Make Project > Make Builder > Workbench Build Behavior > Build (Incremental Build)
    
then enter "release" or "debug". You might need to switch back and forth between
the tabs in the C/C++ Make Project window in order for the options to correctly render.
Else you might just see an empty window.

(Also builds with make alone. Maybe needs new qmake run to setup for your
system, or something.)


HOW TO RUN:

The application takes a single argument which is the configuration
for the scene.

For example run

$ ./crowd cfg/hills.cfg

Make sure LIBGL_ALWAYS_INDIRECT is NOT set and that you have a direct
rendering context, else the application might just fail to start with
a segfault or an error message indicating that no shader program could be
created.

On Ubuntu, if you are running Compiz, gnome-terminals started with keyboard
shortcuts are child processes of compiz and inherit the LIBGL_ALWAYS_INDIRECT
setting. Run the terminal from the Applications menu instead.


HOW TO IDENTIFY KNOWN BUGS:

- In rare cases agents might get stuck at walls while moving away from them.
  I don't know yet what is causing it. Probably only happens at corners.
- Sometimes two agents might meet and get stuck at each other without evading.
  Solving this would require additional local navigation measures like Velocity
  Obstacles.
- Agents move through corner cells at the end of 3 cell wide walls, this is by
  design and a result of how potentials are computed.

- In rare cases the agent count for parked agents might underflow and display
  large numbers. Might be a driver bug, as I can't see any other reason for it.

- Sometimes segfaults in XQueryExtension at exit, probably an X or Qt issue.

