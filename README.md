rsx-debugger is a Qt debugger app aimed at helping debugging rpcs3 rsx emulation.
It requires Qt Core and the Qt QML modules as additionnal build dependencies.

To use it, capture a frame inside rpcs3. This will generates a file in the bin/ directory.
At launch rsx-debugger will load any bin/capture.txt file and display the content in a more friendly maneer.

TODO:
- Provide a "load" menu.
- Display saved surface content.
- Display command dump.

