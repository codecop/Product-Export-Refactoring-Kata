@cls
@color 02
@setlocal
set F=ApprovalsTest

@if exist %F%.exe del %F%.exe
gcc -g -Wall -Wextra -pedantic -std=c99 -O %F%.c -l cmocka -o %F%.exe
@if errorlevel 1 @color 04 && @echo FAILED: %errorlevel% && goto end

%F%.exe
@if errorlevel 1 @color 04 && @echo FAILED: %errorlevel% && goto end

:end
@endlocal
