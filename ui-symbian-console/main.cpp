// Implements an entry point for a Symbian .exe in a Symbian native
// way. Creates a console for displaying any exception.

#include "engine.hpp"

#include "current_config.hrh"

#include <stdexcept>

#include <e32base.h>
#include <e32cons.h>

#if WITH_QT
#include <estlib.h> // __crt0

#include <QtCore/QCoreApplication>
#include <QtGlobal>
#endif

/** May leave or return an error code. */
static TInt doMainL()
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
    _LIT(KFmt, "std::exception occurred: %S");
    TPtrC8 what((const TUint8*)ex.what());
    RBuf16 buf16;
    buf16.CreateL(what.Length());
    buf16.Copy(what); // convert
    console->Printf(KFmt, &buf16);
    buf16.Close();
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
  CleanupStack::PopAndDestroy(console);
  return err;
}

#if WITH_QT
static TInt doSubMainQt(int argc, char *argv[], char *envp[])
{
  // This seems a fairly heavy-duty class. It may be unsafe to try to
  // do anything really after it gets destroyed. Hence we complete
  // cleanup for app proper before letting it fall out of scope.
  QCoreApplication app(argc, argv);

  TRAPD(err, err = doMainL());
  return err;
}

static TInt doMainQtL()
{
  // It is difficult to get init and cleanup right in such a way that
  // QtCoreApplication is happy, and some of the code here closely
  // mirrors code in Qt's s60main. These must persist for as long as
  // QCoreApplication does.
  int argc = 0;
  char **argv = 0;
  char **envp = 0;
  __crt0(argc, argv, envp);
  TRAPD(errCode, 
	QT_TRYCATCH_LEAVING(errCode = doSubMainQt(argc, argv, envp);));
  delete[] argv;
  delete[] envp;
  return errCode;
}
#endif

#if WITH_QT
#define DO_MAIN_LEAVING doMainQtL
#else
#define DO_MAIN_LEAVING doMainL
#endif

GLDEF_C TInt E32Main() // main function called by E32
{
  __UHEAP_MARK;
  CTrapCleanup* cleanup = CTrapCleanup::New();
  TInt err;
  if (cleanup) {
    TRAP(err, err = DO_MAIN_LEAVING());
  } else {
    err = KErrNoMemory;
  }
  _LIT(KAppPanic, "ETA");
  __ASSERT_ALWAYS(!err, User::Panic(KAppPanic, err));
  delete cleanup;
  __UHEAP_MARKEND;
  return err;
}

/**

Copyright 2009-2013 Helsinki Institute for Information Technology
(HIIT), University of Bergen, and the authors. All rights reserved.

Authors: Tero Hasu <tero.hasu@hut.fi>

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation files
(the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

 **/
