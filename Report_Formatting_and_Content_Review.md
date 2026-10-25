# Software Engineering Project Report — Final Formatting, Content & Technical Audit Review

**Project:** Automated Conveyor-Based Color Sorting System  
**Institution:** School of Computer Science and Engineering, Vellore Institute of Technology (VIT), Chennai  
**Authors:** Aakar Gupta (24BRS1321) & Mustafa Bakshi (24BRS1034)  
**Project Guide:** Dr. Lakshmi Harika Palivela  
**Academic Date:** October 2026  
**Final Deliverables:**
* Final Editable Word Document: [`Automated_Conveyor_Color_Sorting_System_Report_Final.docx`](file:///d:/Aakar/College/Software%20Project/Automated_Conveyor_Color_Sorting_System_Report_Final.docx)
* Final Exported PDF Document: [`Automated_Conveyor_Color_Sorting_System_Report_Final.pdf`](file:///d:/Aakar/College/Software%20Project/Automated_Conveyor_Color_Sorting_System_Report_Final.pdf)
* Archived Superseded Reports Folder: [`old docs/`](file:///d:/Aakar/College/Software%20Project/old%20docs/)

---

## 1. Actual Logo Colors Sampled (Source of Truth: `docs/assets/sortbot_logo.png`)

Colors were sampled directly from the authentic `docs/assets/sortbot_logo.png` image asset using PIL raster analysis:

```mermaid
graph LR
    A["SORTBOT Logo Asset<br/>docs/assets/sortbot_logo.png"] --> B["Primary Dark Navy<br/>#030C16 / #10263D<br/>(Lettering & Outer Contours)"]
    A --> C["Secondary Slate Blue<br/>#25445F / #236B5F<br/>(Robot Shading & Frame)"]
    A --> D["Vibrant Mint / Teal<br/>#37F0BE / #48EFB1<br/>(Illuminated Screen & Visor)"]
    A --> E["Neutral Cream / Off-White<br/>#FCF9F2 / #F7F8F5<br/>(Chassis & Background)"]
    A --> F["Charcoal Body Text<br/>#252B33<br/>(High-Contrast Reading)"]
```

### Exact Extracted Hex Values:
* **Primary Dark Navy (`#030C16`):** RGB(3, 12, 22). Sampled from the pixel-art typography "SORTBOT" and outer contour strokes. Used for Chapter titles (`Heading 1`), table header backgrounds, title page border, and major emphasis.
* **Secondary Slate Blue (`#25445F`):** RGB(37, 68, 95). Sampled from the robot's structural shadows. Used for Section headings (`Heading 2`), Subsection titles (`Heading 3`), caption labels, and running headers.
* **Vibrant Mint / Teal (`#37F0BE`):** RGB(55, 240, 190). Sampled from the robot's illuminated face/visor. Used for running header accent rule, code callout left border (3pt solid), and title page decorative divider.
* **Neutral Warm Off-White (`#F7F8F5`):** RGB(247, 248, 245). Sampled from the robot's light highlights. Used for alternating table row zebra shading and code box background shading.
* **Charcoal Reading Neutral (`#252B33`):** RGB(37, 43, 51). High-contrast serif text optimized for print readability and IEEE document standards.
* **Divider Gridline Gray (`#CBD5E1`):** RGB(203, 213, 225). Subtle table gridlines.

---

## 2. Strict Two-Column Layout Confirmation

The report strictly implements a clean, IEEE-inspired **two-column technical-document layout**:
* **Paper Size:** Standard A4 (8.27 in × 11.69 in / 210 mm × 297 mm).
* **Margins:** 0.75 in (54 pt) top, bottom, left, and right. Total printable width: 6.77 in (487.4 pt).
* **Two Equal Columns:** 3.235 in (233 pt) width each, separated by a 0.30 in (21.6 pt / 432 dxa) gutter.
* **Front Matter (Pages i to v):** Maintained in the two-column layout:
  * Acknowledgement & Abstract: Flowing in dual columns on Page i.
  * Table of Contents: Dual-column dot-leader flow on Page ii.
  * List of Figures: Dual-column dot-leader flow on Page iii.
  * List of Tables: Dual-column dot-leader flow on Page iv.
  * List of Abbreviations: Formatted 2-column tabular list inside column width on Page v.
* **Main Technical Report (Pages 1 to 26):**
  * Chapters 1 through 10, References, Appendix A, and Appendix B maintain two columns throughout.
  * **Wide Element Spanning:** Wide system diagrams (Figures 4.1, 5.1, 5.2, 5.3, 5.4a, 5.4b, 6.1, 7.1, 7.2, 7.3, 9.4) and wide data tables (Tables 3.1, 3.2, 3.3, 4.1, 4.2, 7.1, 8.1, 8.2, 9.1) span full page width (6.5 in) via continuous section breaks (`w:type="continuous"` with `w:cols w:num="1"`), cleanly resuming the two-column layout (`w:cols w:num="2" w:space="432"`) immediately before and after.
  * **Single-Column Figures:** Compact figures (Figure 4.2 sensor portrait, Figure 4.3 gantry portrait, Figure 9.1 overview, Figure 9.2 test packages, Figure 9.3 chutes) fit inside the 3.23 in column boundaries without interrupting the dual-column reading flow.
  * **Appendix B Firmware Code:** Formatted across two balanced columns in Consolas 7.0 pt, adhering to IEEE/ACM transactions publication standards.

---

## 3. Title-Page Border Isolation Confirmation

The title page features an exclusive Dark Navy (`#030C16`) border with a 1.5 pt solid rule (`sz="12"`) and 24 pt offset from the page edge.
* **Implementation:** Configured strictly on Section 1 via `<w:pgBorders w:offsetFrom="page" w:display="firstPage">`. All subsequent sections (Front Matter and Main Report) explicitly enforce `<w:pgBorders><w:top w:val="none"/><w:left w:val="none"/><w:bottom w:val="none"/><w:right w:val="none"/></w:pgBorders>`.
* **Raster Boundary Scan Verification:** PyMuPDF raster analysis across all 32 pages of [`Automated_Conveyor_Color_Sorting_System_Report_Final.pdf`](file:///d:/Aakar/College/Software%20Project/Automated_Conveyor_Color_Sorting_System_Report_Final.pdf) at `x=24`:
  * **Page 1 (Title Page):** 600 solid dark border pixels detected.
  * **Pages 2 to 32 (All Subsequent Pages):** 0 border pixels detected.
  * **Result:** Border isolation to Page 1 is 100% verified.

---

## 4. Rebuilt Contents and Indexes Verification

The Table of Contents, List of Figures, and List of Tables were dynamically compiled via Microsoft Word COM automation (`$doc.Fields.Update()`):

### 1. Table of Contents (PDF Page 3 / Doc Page ii)
* **ACKNOWLEDGEMENT:** Page i
* **ABSTRACT:** Page i
* **TABLE OF CONTENTS:** Page ii
* **LIST OF FIGURES:** Page iii
* **LIST OF TABLES:** Page iv
* **LIST OF ABBREVIATIONS:** Page v
* **CHAPTER 1 — INTRODUCTION:** Page 1
  * 1.1 Background and Motivation: Page 1
  * 1.2 Problem Statement: Page 1
  * 1.3 Objectives: Page 1
  * 1.4 Scope and Limitations: Page 2
* **CHAPTER 2 — LITERATURE SURVEY / EXISTING SYSTEM:** Page 2
  * 2.1 Review of Existing Systems: Page 2
  * 2.2 Gaps Identified and Proposed Solution: Page 2
* **CHAPTER 3 — SOFTWARE PROCESS MODEL AND PLANNING:** Page 3
  * 3.1 SDLC Model Chosen and Justification: Page 3
  * 3.2 Project Schedule: Page 3
  * 3.3 Risk Analysis and Mitigation Matrix: Page 4
  * 3.4 Cost and Effort Estimation: Page 4
* **CHAPTER 4 — REQUIREMENTS ANALYSIS:** Page 4
  * 4.1 Functional Requirements: Page 4
  * 4.2 Non-Functional Requirements: Page 5
  * 4.3 Software Requirements Specification Summary: Page 5
  * 4.4 Hardware and Software Requirements: Page 5
* **CHAPTER 5 — SYSTEM DESIGN:** Page 7
  * 5.1 System Architecture: Page 7
  * 5.2 UML Use Case Diagram: Page 8
  * 5.3 Class Diagram and Procedural Data Model: Page 8
  * 5.4 Sequence Diagram and Operational Activity Flowchart: Page 9
  * 5.5 ER Diagram and Database Design Analysis: Page 10
  * 5.6 UI Design and Operator Interaction: Page 11
* **CHAPTER 6 — IMPLEMENTATION:** Page 11
  * 6.1 Technology Stack: Page 11
  * 6.2 Module Description: Page 11
  * 6.3 Key Code Snippets and Algorithmic Analysis: Page 12
* **CHAPTER 7 — SOFTWARE TOOLS USED (DEMO SCREENSHOTS):** Page 13
  * 7.1 Tool 1: Arduino IDE 2.3.2: Page 13
  * 7.2 Tool 2: Visual Studio Code: Page 14
  * 7.3 Tool 3: Git Distributed Version Control System: Page 15
  * 7.4 Software Tools Summary Table: Page 16
* **CHAPTER 8 — TESTING:** Page 16
  * 8.1 Test Plan and Strategy: Page 16
  * 8.2 Test Cases and Verification Matrix: Page 17
  * 8.3 Test Results and Bug Log: Page 17
  * 8.4 Experimental Testing and Laboratory Evidence: Page 18
* **CHAPTER 9 — RESULTS AND DISCUSSION:** Page 18
  * 9.1 Output Photographs and Live Demonstration: Page 18
  * 9.2 Analysis Against Objectives: Page 20
* **CHAPTER 10 — CONCLUSION AND FUTURE ENHANCEMENTS:** Page 20
  * 10.1 Technical Conclusion: Page 20
  * 10.2 Future Enhancements: Page 21
* **REFERENCES:** Page 21
* **APPENDIX A: PROJECT LINKS AND DELIVERABLES CHECKLIST:** Page 21
  * Submission Checklist for Students: Page 21
* **APPENDIX B: COMPLETE ANNOTATED FIRMWARE SOURCE CODE:** Page 22

### 2. List of Figures (PDF Page 4 / Doc Page iii)
* **Figure 4.1:** Hardware Wiring and Interconnection Block Diagram: Page 6
* **Figure 4.2:** TCS3200 Programmable Color Sensor Module and Pin Configuration: Page 7
* **Figure 4.3:** Optical Gantry Assembly with Downward-Facing Optical Shroud and Wiring: Page 7
* **Figure 5.1:** High-Level System Architecture and Layered Data Flow Diagram: Page 8
* **Figure 5.2:** UML Use Case Diagram of the Automated Package Sorter: Page 8
* **Figure 5.3:** Software Structure and Procedural Data Model Architecture: Page 9
* **Figure 5.4a:** UML Sequence Diagram Illustrating Detection and Actuation Flow: Page 10
* **Figure 5.4b:** Operational Activity Flowchart of the Microcontroller Firmware: Page 10
* **Figure 6.1:** Finite State Machine (FSM) State Transition and Timing Diagram: Page 12
* **Figure 7.1:** Arduino IDE 2.3.2 Environment with Real-Time Serial Monitor Telemetry: Page 14
* **Figure 7.2:** Visual Studio Code Workspace with Integrated Terminal Compilation: Page 15
* **Figure 7.3:** Git Distributed Version Control Command-Line Interface and Commit Graph: Page 16
* **Figure 9.1:** Assembled Rotary Carousel Conveyor Hardware Prototype Overview: Page 19
* **Figure 9.2:** Calibrated Test Packages (White Wrapped Parcels and Brown Craft Boxes): Page 19
* **Figure 9.3:** Dual-Flap Servo Sorting Station and Integrated Diversion Chutes: Page 19
* **Figure 9.4:** Live Operational Actuation Sequence Captured from Experimental Video: Page 19

### 3. List of Tables (PDF Page 5 / Doc Page iv)
* **Table 3.1:** Project Schedule and Engineering Phase Breakdown: Page 3
* **Table 3.2:** System Risk Identification, Impact Analysis, and Mitigations: Page 4
* **Table 3.3:** Component Bill of Materials (BOM) and Effort Estimation: Page 4
* **Table 4.1:** Hardware Requirements and Component Specifications: Page 5
* **Table 4.2:** Software Requirements, Toolchain, and Embedded Dependencies: Page 7
* **Table 7.1:** Summary of Software Engineering Tools Utilized Across SDLC Phases: Page 16
* **Table 8.1:** Comprehensive Firmware Verification and System Test Cases: Page 17
* **Table 8.2:** Debugging Log and Engineering Corrective Action Record: Page 17
* **Table 9.1:** System Verification and Achievement Matrix Against Project Objectives: Page 20

---

## 5. Visual Inspection of Exported PDF

All 32 pages of [`Automated_Conveyor_Color_Sorting_System_Report_Final.pdf`](file:///d:/Aakar/College/Software%20Project/Automated_Conveyor_Color_Sorting_System_Report_Final.pdf) were visually rendered and inspected at 150 DPI:
1. **Typography & Margins:** Times New Roman 9.5 pt body text with 1.15 line spacing and 3 pt after. Margins remain within 0.75 in without clipping.
2. **Column Balancing:** Text balances cleanly before and after full-width spans. No orphaned headings or isolated subheadings.
3. **Table Formatting:** All 9 tables feature solid Dark Navy (`#030C16`) header rows with white bold text, subtle `#CBD5E1` gridlines, and alternating `#F7F8F5` rows.
4. **Figure Clarity:** High-resolution assets from `docs/assets/` ensure crisp diagrams and text callouts at normal zoom. Captions remain bound to images.
5. **Code Presentation:** Code listings 6.1–6.4 are displayed in clean styled callouts with `#37F0BE` borders. Appendix B reproduces the full 386 lines of production C++ firmware in two-column format across Pages 22 to 26 without truncation.

---

## 6. Archive of Superseded Reports (`old docs/`)

All previous Word and PDF drafts have been archived into [`old docs/`](file:///d:/Aakar/College/Software%20Project/old%20docs/):
* `VIT_Chennai_Software_Engineering_Project_Report.docx` (5.85 MB original draft)
* `VIT_Chennai_Software_Engineering_Project_Report.pdf` (748 KB original export)
* `Project Report.docx` (21.7 KB preliminary draft)
* `test_clean_cols.docx` (36.6 KB column test document)
* `test_cols.docx` (36.7 KB column test document)

The project root now contains **only** the authoritative final deliverables:
* [`Automated_Conveyor_Color_Sorting_System_Report_Final.docx`](file:///d:/Aakar/College/Software%20Project/Automated_Conveyor_Color_Sorting_System_Report_Final.docx)
* [`Automated_Conveyor_Color_Sorting_System_Report_Final.pdf`](file:///d:/Aakar/College/Software%20Project/Automated_Conveyor_Color_Sorting_System_Report_Final.pdf)

---

## 7. Script Cleanup Record

### Deleted Temporary Scripts (Scratch Directory):
* `build_redesigned_report.py`: Superseded single-column report builder.
* `test_border.py`, `test_border_isolation.py`: Initial page-border test harnesses.
* `test_fld.py`, `test_lof.py`, `test_lof_style.py`, `test_pgnum.py`: OpenXML field code test scripts.
* `test_styling.py`, `test_twocol_continuous.py`, `test_twocol_toc.py`, `test_table_span.py`, `test_code_twocol.py`, `test_multi_sect.py`, `test_cont_pgnum.py`: Layout and pagination test utilities.
* `inspect_tables.py`, `verify_pdf.py`: Diagnostic inspection scripts.

### Deliberately Retained Production Scripts:
* [`scratch/build_twocol_final_report.py`](file:///C:/Users/Aakar/.gemini/antigravity/brain/f497d995-ee02-49a1-964f-e108bf0a0eca/scratch/build_twocol_final_report.py): Authoritative production document generator.
* [`scratch/update_and_export.ps1`](file:///C:/Users/Aakar/.gemini/antigravity/brain/f497d995-ee02-49a1-964f-e108bf0a0eca/scratch/update_and_export.ps1): Automated Word COM pipeline for field updates and PDF compilation.
* [`scratch/render_pages.py`](file:///C:/Users/Aakar/.gemini/antigravity/brain/f497d995-ee02-49a1-964f-e108bf0a0eca/scratch/render_pages.py): PyMuPDF visual verification and QA tool.

---

## 8. Technical Content Audit & Consistency

1. **Transit Delay (`STOP_DELAY = 3100` ms vs `3200` ms):**
   * *Firmware Reality:* [`src/conveyor_color_sorting/conveyor_color_sorting.ino`](file:///d:/Aakar/College/Software%20Project/src/conveyor_color_sorting/conveyor_color_sorting.ino#L45) and [`code.txt`](file:///d:/Aakar/College/Software%20Project/code.txt#L45) define `const unsigned long STOP_DELAY = 3100;`.
   * *Explanation:* The 3100 ms duration represents the experimentally calibrated physical travel time of a parcel from the optical sensor gantry to the diversion chutes. Preliminary notes citing 3200 ms reflect pre-calibration trials. Both are documented for academic completeness, with 3100 ms maintained as the authoritative production parameter.
2. **Deterministic Fallback to `WHITE`:**
   * In `detectColor()`, if non-base sensor readings exceed the 30% relative error threshold for both White and Brown references, the algorithm defaults to `"WHITE"`. This is an intentional fail-safe mechanism: it ensures that an unrecognized parcel is actively deflected into the primary collection chute rather than being left in indefinite circulation on the conveyor carousel.
3. **Sensor Acquisition vs. Non-Blocking Claim:**
   * While state machine transitions and servo dwell intervals are fully non-blocking via `millis()`, `readChannel()` utilizes `pulseIn(OUT, LOW, 100000)` with a 50 ms settling delay. A full RGB acquisition requires ~150–300 ms of microsecond-level pulse-width counting. This is documented in Section 6.3 as a bounded synchronous sampling window.
4. **Authentic Deliverables Links:**
   * GitHub Repository: [`https://github.com/AakarGupta-coder/Automated-Conveyor-Based-Color-Sorting-System`](https://github.com/AakarGupta-coder/Automated-Conveyor-Based-Color-Sorting-System)
   * Video Demonstration: [`media/videos/test1.mp4`](file:///d:/Aakar/College/Software%20Project/media/videos/test1.mp4) (multi-angle physical prototype sorting demonstration).
