#pragma once
// menu.h
// Menu subsystems, performance analysis, and insights

// Sub-menu for a single city dataset
// cityLabel : "City A" / "City B" / "City C"
// displayName: label shown in headers
void datasetSubMenu(const char *cityLabel, const char *displayName);

// Sub-menu for all three datasets combined
void combinedMenu();

// Top level individual dataset selection menu
void individualMenu();

// Performance analysis overview (Array data structure)
void performanceAnalysis();

