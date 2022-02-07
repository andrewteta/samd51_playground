@echo off

call "C:\Users\andre\miniconda3\Scripts\activate.bat"
call conda activate uf2
call python "C:\Users\andre\github\uf2\utils\uf2conv.py" -b 0x4000 -c -o "C:\Users\andre\OneDrive\Documents\_dev\samd\samd51j19a_1\samd51j19a_1\Debug\samd51j19a_1.uf2" "C:\Users\andre\OneDrive\Documents\_dev\samd\samd51j19a_1\samd51j19a_1\Debug\samd51j19a_1.bin"
