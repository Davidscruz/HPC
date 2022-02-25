@echo off
set list= 10 100 250 500 1000 2000 3000
for /l %%x in (1,1,5) do (
    for %%y in (%list%) do (
        secuencial.exe %%y >> resultados.csv
    )
)

pause