# Projections And Shadows OpenGL C++

Projections And Shadows OpenGL C++  crislanio.wordpress.com

- Projeto para IDE **QtCreator** utilizando *C++, OpenGL, GLUT/Qt*;

## Dependências
- C++
- QtCreator
- OpenGL
- GLUT/Qt

## Instalação
- G++:
- sudo apt update
 - sudo apt install g++
 
- GLUT:
- sudo apt install freeglut3-dev

- MALHAS 3D:
- sudo apt install lib3ds-dev

- IMAGENS/TEXTURAS:
- sudo apt install libdevil-dev

- SDL:
- sudo apt install libsdl1.2-dev
- sudo apt install libsdl-image1.2-dev

- QT: siga o tutorial abaixo:
- https://wiki.qt.io/Install_Qt_5_on_Ubuntu

- OpenGL: siga o tutorial abaixo:
- https://pt.wikibooks.org/wiki/Programa%C3%A7%C3%A3o_com_OpenGL/Instala%C3%A7%C3%A3o/Linux




| Aplicação                     | Versão        |
| :---------------------------- |:-------------:|
| Projections And Shadows OpenGL C++            | 1.0.0           |

## Objetivos do trabalho
- Projeções
  - alternar entre proj. perspectiva e proj. ortográfica
    - usando alguma tecla
  - definir posições/orientações de câmera específicas para simular todas as possíveis projeções
   clássicas, de acordo com a classificação mostrada em sala
    - não precisa simular as projeções oblíquas
    - pode focar em um objeto específico
  - permitir alternar entre essas posições/orientações pré-estabelecidas usando o teclado
- Sombras
  - mostrar as sombras de todos os objetos
  - no chão (plano horizontal) e em uma parede qualquer (plano vertical)
    - mostrar resultado da sombra em um canto de parede
  - alternar entre luz pontual (proj. perspectiva) e luz distante (proj. oblíqua)
- Sugestão: usar C++, QtCreator, OpenGL, GLUT/Qt
### Screenshots
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/1.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/2.png)

![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/LuzNoInfinito.jpg)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/OrthoDimetric.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/OrthoDimetric.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/OrthoFrontObj.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/OrthoIsometric.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/OrthoPlanObj.png)![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/OrthoSideObj.png)![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/OrthoTrimetric.png)![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/Perspective1pontoF.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/Perspective2PlanoF.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/Perspective3PlanoF.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/orthoDimetric2.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/orthoFrontElevation.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/orthoIsometric.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/orthoPlanElevation.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/orthoSideElevation.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/orthoTrimetric.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/perspective1PP.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/perspective1PointP.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/perspective2PP.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/perspective1PP.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/perspective2PointP.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/perspective3PP.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/perspective3PointP.png)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/sombraNaQ.png)

### Matrizes para gerar as sombras
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/gerarMatrizSombraFoto0_X=k.jpg)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/gerarMatrizSombraFoto1_X=k.jpg)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/gerarMatrizSombraY=0.jpeg)
![alt tag](https://raw.githubusercontent.com/crislanio/Projections_And_ShadowsOpenGL/master/PROJEÇÕES_E_SOMBRAS/imgs/gerarMatrizSombraZ=k.jpg)

