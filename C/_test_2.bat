@cls
@color 02
@setlocal
@for /r %%f in (*Test.c) do set F=%%~nf
set F=XMLExporterTest2

@if exist %F%.exe del %F%.exe
gcc -g -Wall -Wextra -pedantic -std=c99 -O LinkedList.c LinkedMap.c Price.c Product.c Order.c Store.c StoreEvent.c Util.c TaxCalculator.c SampleModelObjects2.c StringBuilder.c XMLExporter.c mu_approvals\Approvals.c %F%.c -l cmocka -o %F%.exe
@if errorlevel 1 @color 04 && @echo FAILED: %errorlevel% && goto end

%F%.exe
@if errorlevel 1 @color 04 && @echo FAILED: %errorlevel% && goto end

:end
@endlocal
