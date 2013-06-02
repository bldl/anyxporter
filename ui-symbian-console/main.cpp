// Implements an entry point for a Symbian .exe in a Symbian native
// way. Creates a console for displaying any exception.

#include "engine.hpp"

#include "current_config.hrh"

#include <stdexcept>

#include <e32base.h>
#include <e32cons.h>

static void doMainL()
{
  _LIT(KConsoleTitle, "ExporTemplApp");
  CConsoleBase* console = Console::NewL(KConsoleTitle,
					TSize(KConsFullScreen,
					      KConsFullScreen));
  CleanupStack::PushL(console);
  TInt err = 0;
  try {
    engine::exportData();
  } catch (const std::exception& ex) {
    err = 1;
    _LIT(KFmt, "std::exception occurred: %s");
    TPtrC8 ptr((const TUint8*)ex.what());
    console->Printf(KFmt, &ptr);
  } catch(...) {
    err = 2;
    _LIT(KFmt, "non-std::exception occurred");
    console->Printf(KFmt);
  }
  if (!err) {
    _LIT(KAllDone, "All done.");
    console->Printf(KAllDone);
  }
  _LIT(KPressAnyKey, " [press any key]");
  console->Printf(KPressAnyKey);
  console->Getch();
  if (err)
    User::Leave(err);
  CleanupStack::PopAndDestroy(console);
}

GLDEF_C TInt E32Main() // main function called by E32
{
  __UHEAP_MARK;
  CTrapCleanup* cleanup = CTrapCleanup::New();
  TRAPD(err, doMainL());
  _LIT(KAppPanic, "ETA");
  __ASSERT_ALWAYS(!err, User::Panic(KAppPanic, err));
  delete cleanup;
  __UHEAP_MARKEND;
  return 0;
}
