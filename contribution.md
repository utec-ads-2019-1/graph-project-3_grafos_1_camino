# Creen su rama y commiteen en ella :)

Crear rama
```bash
git checkout -b Daniel
```

Subir cambios a mi rama
```
git add --all
git commit -m 'Avance'
git push origin Daniel
```

Actualizar mi rama con master
```bash
git checkout Daniel
git pull
git merge master
```

Poner los cambios de mi rama en master
```bash
git checkout master
# Asegurate de haber hecho el paso anterior
git merge Daniel
# Arregla conflictos si los hay, asegurate que todo corra
git push origin master
```
