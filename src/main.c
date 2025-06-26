#include "webview/webview.h"
#include <stddef.h>

extern unsigned char index_modified[];
extern unsigned int index_modified_len;

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#import <Cocoa/Cocoa.h>
#include <objc/message.h>
#include <objc/runtime.h>

// TODO: window can't be moved without titlebar
void hide_title_bar(void *webview_window) {
  NSWindow *window = (NSWindow *)webview_window;
  [window setTitleVisibility:NSWindowTitleHidden];
  [window setTitlebarAppearsTransparent:YES];
  [window setStyleMask:[window styleMask] | NSWindowStyleMaskFullSizeContentView];
  [window setMovableByWindowBackground:YES]; // <-- should allow drag from background

  [[window standardWindowButton:NSWindowCloseButton] setHidden:YES];
  [[window standardWindowButton:NSWindowMiniaturizeButton] setHidden:YES];
  [[window standardWindowButton:NSWindowZoomButton] setHidden:YES];

}
#endif

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {
  (void)hInst;
  (void)hPrevInst;
  (void)lpCmdLine;
  (void)nCmdShow;

  putenv("WEBVIEW2_ADDITIONAL_BROWSER_ARGUMENTS=--autoplay-policy=no-user-gesture-required");
#else
int main(void) {
#endif
  webview_t w = webview_create(0, NULL);
  webview_set_title(w, "Basic Example");
  webview_set_size(w, 800, 600, WEBVIEW_HINT_FIXED);
  webview_set_html(w, (const char *)index_modified);

#ifdef __APPLE__
  void *native_window = webview_get_window(w);
  if (native_window) {
    hide_title_bar(native_window);
  }
#endif

  webview_run(w);
  webview_destroy(w);
  return 0;
}
