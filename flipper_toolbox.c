// This app made by khalifa for fun and learning .

#include <furi.h>
#include <gui/gui.h>
#include <input/input.h>
#include <stdlib.h>
#include <gui/elements.h>

// Structure for app information
typedef struct
{
    const char *title;
    const char *subtitle;
} AppInfo;

// Array of apps
const AppInfo apps[] = {
    {"Sub-GHz Bruteforcer", "A tool for Sub-GHz frequency bruteforcing"},
    {"NFC Cloner", "Clone NFC tags"},
    {"IR Remote", "Control devices using infrared"},
    {"RFID Fuzzer JJ", "A tool for fuzzing RFID systems"},
    {"USB Fuzzer", "Fuzzing tool for USB interfaces"},
    {"BT Trigger", "Bluetooth triggering tool"},
    {"Weather Station", "Monitor weather parameters"},
    {"iButton", "Tool for iButton devices"},
    {"RFID Beacon", "RFID signal beacon tool"},
    {"Astroturkv2", "Miscellaneous tool"},
    {"PicoPass", "NFC tool for PicoPass tags"},
    {"Mfkey32", "Mifare key tool"},
    {"Mifare Fuzzer", "Fuzzer for Mifare systems"},
    {"Nfc Magic", "NFC manipulation tool"},
    {"NFC Maker", "NFC tag creation tool"},
    {"Flipper Nested", "Nested operation tool for Flipper"},
    {"MFKey", "Mifare key extraction tool"},
    {"NFC Magic [Gen4]", "Fourth generation NFC Magic tool"},
    {"Xbox Controller", "Xbox controller tool"},
    {"Cross Remote", "Cross-platform remote control tool"},
    {"XRemote", "Extended remote control tool"},
    {"[Sony] Intervalometer", "Intervalometer for Sony devices"},
    {"[ESP32] Evil Portal", "ESP32-based portal tool"},
    {"ESP Flasher", "Flasher tool for ESP devices"},
    {"UltraFlashlight", "Advanced flashlight tool"},
    {"RC2014 ColecoVision", "ColecoVision tool for RC2014"},
    {"[MAYHEM] Marauder v0.6.4", "Marauder tool version 0.6.4"},
    {"Servo Tester", "Tester for servo motors"},
    {"I2C Demo", "Demonstration tool for I2C protocol"},
    {"iButton Fuzzer", "Fuzzer for iButton devices"},
    {"BLE Spam", "Bluetooth Low Energy spamming tool"},
    {"Apple BLE Spam", "BLE spamming tool for Apple devices"},
    {"Cookie Clicker", "Cookie clicking game"},
    {"USB Midi", "MIDI interface for USB"},
    {"Bad USB", "Tool for creating malicious USB devices"},
    {"BarCode ScannerE", "Barcode scanning tool"},
    {"Mass Storage", "Mass storage tool"},
    {"Remote", "Remote control tool"},
    {"USB HID Autofire", "Autofire tool for USB HID"},
    {"2048 (Improved)", "Improved version of 2048 game"},
    {"BlackJack", "Blackjack card game"},
    {"Color Guess", "Color guessing game"},
    {"Dice D&D", "Dice tool for Dungeons & Dragons"},
    {"DOOM", "DOOM game"},
    {"City Bloxx", "City building game"},
    {"Sudoku", "Sudoku puzzle game"},
    {"Game 15", "15 puzzle game"},
    {"Tetris", "Tetris game"},
    {"Solitaire", "Solitaire card game"},
    {"Tone generator", "Audio tone generator"},
    {"Flizzer Tracker", "Tracker tool for Flizzer"},
    {"Music Player", "Digital music player"},
    {"WAV Player", "WAV format audio player"},
    {"BPM Tapper", "Beats per minute tapper tool"},
    {"Video Player", "Digital video player"},
    {"SAM AYBABTU", "SAM-based tool"},
    {"Metronome", "Musical metronome tool"},
    {"Tuning Fork", "Digital tuning fork"},
    {"WHC SWIO Flasher", "Flasher tool for WHC SWIO"},
    {"BadBT", "Bluetooth vulnerability tool"},
    {"UnZip (in dev)", "Unzipping tool (in development)"},
    {"Hex Viewer", "Tool for viewing hexadecimal data"},
    {"Bad KB", "Tool for creating malicious keyboards"},
    {"RFID detector", "Detector for RFID tags"},
    {"Nightstand Clock", "Digital nightstand clock"},
    {"Barcode", "Barcode generation and reading tool"},
    {"Orgasmotron", "Miscellaneous tool"},
    {"EM4100 Key generator", "Key generator for EM4100"},
    {"LF-RFID Debug", "Debugging tool for LF-RFID"},
    {"FAP Boilerplate", "Boilerplate tool"},
    {"Intervalometer", "Intervalometer tool"},
    {"jClock", "Digital clock tool"},
    {"Counter", "Digital counter tool"},
    {"Multi Converter", "Multipurpose conversion tool"},
    // Add more apps here
};

const size_t apps_count = sizeof(apps) / sizeof(apps[0]);

// Current app index
size_t current_app_index = 0;
bool running = true; // Global flag to control the running state

// Render callback function
static void render_callback(Canvas *const canvas, void *ctx)
{
    (void)ctx;
    char index_info[50];

    // Get the current app
    const AppInfo *current_app = &apps[current_app_index];

    // Set font for the title
    canvas_set_font(canvas, FontPrimary);
    // Draw the title
    elements_multiline_text_aligned(canvas, 64, 15, AlignCenter, AlignTop, current_app->title);

    // Adjust vertical space between title and subtitle
    const int subtitleYPos = 30; // Reduced vertical space for subtitle
    const int indexYPos = 10;    // Position index info closer to the title

    // Set font for the subtitle
    canvas_set_font(canvas, FontSecondary);
    // Draw the subtitle
    elements_multiline_text_aligned(canvas, 64, subtitleYPos, AlignCenter, AlignTop, current_app->subtitle);

    // Set font for index info
    canvas_set_font(canvas, FontSecondary);
    // Format and draw index info
    snprintf(index_info, sizeof(index_info), "%zu of %zu", current_app_index + 1, apps_count);
    elements_multiline_text_aligned(canvas, 64, indexYPos, AlignCenter, AlignBottom, index_info);
}

// Input callback function
void input_callback(InputEvent *input_event, void *ctx)
{
    (void)ctx;

    if (input_event->type == InputTypeShort)
    {
        switch (input_event->key)
        {
        case InputKeyRight:
            current_app_index = (current_app_index + 1) % apps_count;
            break;
        case InputKeyLeft:
            current_app_index = (current_app_index + apps_count - 1) % apps_count;
            break;
        case InputKeyBack: // Exit the app when the Back button is pressed
            running = false;
            break;
        default:
            // Handle other keys or ignore
            break;
        }
    }
}

// Main application function
int32_t flipper_toolbox_app(void)
{
    // Create a viewport
    ViewPort *view_port = view_port_alloc();
    view_port_draw_callback_set(view_port, render_callback, NULL);
    view_port_input_callback_set(view_port, input_callback, NULL);

    // Setup GUI
    Gui *gui = furi_record_open(RECORD_GUI);
    gui_add_view_port(gui, view_port, GuiLayerFullscreen);

    // Main loop to keep the app running
    // Main loop to keep the app running
    while (running)
    {
        // Update the viewport to refresh the screen
        view_port_update(view_port);
        // Sleep for a short duration
        furi_delay_ms(100);
    }

    // Cleanup
    view_port_enabled_set(view_port, false);
    gui_remove_view_port(gui, view_port);
    furi_record_close(RECORD_GUI);
    view_port_free(view_port);

    return 0;
}
