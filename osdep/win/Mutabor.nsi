; Our name
!define PACKAGE_NAME "Mutabor"
!define PACKAGE_VERSION "4.0.0beta3"
!define NAME_VERSION "${PACKAGE_NAME} ${PACKAGE_VERSION}"
!define NAME_VERSION_BUNDLE "${PACKAGE_NAME}-${PACKAGE_VERSION}"
!define EXENAME "mutabor"
!define MUTSHORTCUTDIR "$SMPROGRAMS\${PACKAGE_NAME}"
!define INSTALLATIONNAME "${PACKAGE_NAME}"
!define srcdir "../../../mutabor-git"

Name "${NAME_VERSION}"

; name the installer
outFile "${NAME_VERSION_BUNDLE}.exe"
 
; define the directory to install to, the desktop in this case as specified  
; by the predefined $DESKTOP variable
installDir "$PROGRAMFILES\${PACKAGE_NAME}"
 
; configure used pages
Page license
Page components
Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

LicenseData "Mutabor/GPL-2.txt"


; default section start; every NSIS script has at least one section.
section "Mutabor binaries"
  sectionIn RO

  ; define the output path for this file
  setOutPath $INSTDIR
 
 ; define uninstaller
 writeUninstaller $INSTDIR\Uninstall.exe
 WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${INSTALLATIONNAME}" "DisplayName" "${NAME_VERSION}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${INSTALLATIONNAME}" "UninstallString" '"$INSTDIR\Uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${INSTALLATIONNAME}" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${INSTALLATIONNAME}" "NoRepair" 1

  ; define the output path for this file
  ; doesn't work  ${file} /r  "Mutabor/*.*"
  !include "mutabor-files.nsh"

  ; create a popup box, with an OK button and the text "Hello world!"
  ; messageBox MB_OK "Log has been saved on Desktop."

  ; default section end
sectionEnd

!include mutabor-dirs.nsh

section "Create Start Menu entries"
  ; create a shortcut named "new shortcut" in the start menu programs directory
  ; point the new shortcut at the program uninstaller
  createShortCut "${MUTSHORTCUTDIR}\${PACKAGE_NAME}.lnk" "$INSTDIR\${EXENAME}"

  ; create a shortcut named "new shortcut" in the start menu programs directory
  ; point the new shortcut at the program uninstaller
  createShortCut "${MUTSHORTCUTDIR}\Uninstall ${PACKAGE_NAME}.lnk" "$INSTDIR\Uninstall.exe"
sectionEnd

section "Create desktop shortcut"
  ; create a shortcut named "new shortcut" in the start menu programs directory
  ; point the new shortcut at the program uninstaller
  createShortCut "$DESKTOP\${PACKAGE_NAME}.lnk" "$INSTDIR\${EXENAME}"
sectionEnd

;-----------------------------------------------------------------
; create a section to define what the uninstaller does.
; the section will always be named "Uninstall"
section "Uninstall"
  ; fix up other stuff
  !include "mutabor-uninst-files.nsh"

  delete $INSTDIR\Uninstall.exe

  ; delete start menu items
  delete "${MUTSHORTCUTDIR}\${PACKAGE_NAME}.lnk"
  delete "${MUTSHORTCUTDIR}\Uninstall ${PACKAGE_NAME}.lnk"

  RMDir $INSTDIR 

  ; clear Registry
  DeleteRegKey HKU "Software\mutabor"
  DeleteRegKey HKCU "Software\mutabor"
  DeleteRegKey HKLM "Software\mutabor"
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${INSTALLATIONNAME}"
sectionEnd
