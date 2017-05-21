

#prepare translations
UGENE_TRANSL_IDX   = 0          1
UGENE_TRANSL_FILES = russian.ts english.ts
UGENE_TRANSL_TAG   = ru         en

UGENE_TRANSL_DIR   = transl
UGENE_TRANSL_QM_TARGET_DIR = $$OUT_PWD/src/_debug $$OUT_PWD/src/_release

#detecting lrelease binary
win32 : UGENE_DEV_NULL = nul
unix : UGENE_DEV_NULL = /dev/null

UGENE_LRELEASE =
UGENE_LUPDATE =
message(Using QT from $$[QT_INSTALL_BINS])
system($$[QT_INSTALL_BINS]/lrelease-qt5 -version > $$UGENE_DEV_NULL 2> $$UGENE_DEV_NULL) {
    UGENE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease-qt5
    UGENE_LUPDATE = $$[QT_INSTALL_BINS]/lupdate-qt5
} else : system($$[QT_INSTALL_BINS]/lrelease -version > $$UGENE_DEV_NULL 2> $$UGENE_DEV_NULL) {
    UGENE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease
    UGENE_LUPDATE = $$[QT_INSTALL_BINS]/lupdate
}

#foreach 'language'
for( i, UGENE_TRANSL_IDX ) {
    UGENE_TRANSLATIONS = 

    curTranslFile = $$member( UGENE_TRANSL_FILES, $$i )
    curTranslTag  = $$member( UGENE_TRANSL_TAG, $$i )

    #foreach project directory
    for( prj_dir, SUBDIRS ) {
        #look for file and add it to translation list if it exists
        translFile = $$prj_dir/$$UGENE_TRANSL_DIR/$$curTranslFile   # 'project/transl/english.ts' etc.
        exists( $$translFile ) {
            UGENE_TRANSLATIONS += $$translFile
#            system( $$UGENE_LUPDATE $$translFile ) FIXME
        }
    }
    !isEmpty(UGENE_LRELEASE) {
        for( targetDir, UGENE_TRANSL_QM_TARGET_DIR ) {
            targetQmFile = $$targetDir/transl_$$curTranslTag            # 'transl_en.qm' etc.
            targetQmFile = $$join( targetQmFile, , , .qm )              # special workaround for adding suffix started with '.'
            message( Generating traslations for language: $$curTranslTag )
            system( $$UGENE_LRELEASE $$UGENE_TRANSLATIONS -qm $$targetQmFile > $$UGENE_DEV_NULL )
        }
    } else {
        message( Cannot generate translations: no lrelease binary found )
    }
}