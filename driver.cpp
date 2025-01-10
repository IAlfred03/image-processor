#include "image.h"

int main(int argc, char** argv) {
    image test("test.png");
    if (!test.data) {
        cerr << "[ERROR] Main: Failed to load test.png. Exiting." << endl;
        return EXIT_FAILURE;
    }

    if (!test.write("new.png")) {
        cerr << "[ERROR] Main: Failed to write new.png." << endl;
    }

    image copy = test;
    if (copy.data) {
        for (int i = 0; i < copy.w * copy.channels; ++i) {
            copy.data[i] = 0;
        }
        if (!copy.write("copy.png")) {
            cerr << "[ERROR] Main: Failed to write copy.png." << endl;
        }
    } else {
        cerr << "[ERROR] Main: Copy failed. No data in the copied image." << endl;
    }

    image blank(100, 100, 3);
    if (!blank.write("blank.jpg")) {
        cerr << "[ERROR] Main: Failed to write blank.jpg." << endl;
    }

    cout << "[DEBUG] Main: Program finished successfully." << endl;
    return 0;
}