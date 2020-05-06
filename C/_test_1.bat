@cls
@color 02
@setlocal
@set F=XMLExporterTest

@if exist %F%.exe del %F%.exe
gcc -g -Wall -Wextra -pedantic -std=c99 -O LinkedList.c LinkedMap.c Price.c Product.c Order.c Store.c StoreEvent.c Util.c TaxCalculator.c StringBuilder.c XMLExporter.c SampleModelObjects.c mu_approvals\approvals.c %F%.c -l cmocka -o %F%.exe
@if errorlevel 1 @color 04 && @echo FAILED: %errorlevel% && goto end

%F%.exe
@if errorlevel 1 @color 04 && @echo FAILED: %errorlevel% && goto end

:end
@endlocal
