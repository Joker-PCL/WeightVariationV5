SET(SOURCES screens/ui_LoadingPage.c
    screens/ui_LoginPage.c
    screens/ui_WeighingPage.c
    screens/ui_ThicknessPage.c
    screens/ui_TabletCharacteristicsPage.c
    screens/ui_SummaryPage.c
    screens/ui_SettingPage.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_402937210.c
    images/ui_img_206557904.c
    images/ui_img_1636676910.c
    fonts/ui_font_ProtestGuerrilla48.c
    fonts/ui_font_Sarabun28.c)

add_library(ui ${SOURCES})
