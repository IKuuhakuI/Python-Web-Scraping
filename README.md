<h1> Trabalho Final: C++ e Python Web Scraping </h1>
<h4> Por: Luiz Carlos Aguiar Carrion e Maria Eduarda Mafra </h4>

<h2> Objetivo </h2>
<p> O objetivo do trabalho é o de criar uma aplicação que integre duas linguagens de programação diferentes. Para o projeto, as linguagens escolhidas foram o C++ e Python3 </p>
<p> Como tema do trabalho, decidimos implementar um programa para fazer web scraping em sites de compras online (amazon, americanas e submarino). </p>

<h2> Requisitos </h2>
<p> Versão do Python: 3.8 </p>
<p> Versão do C++: 11 </p>

<p> Instalar: python3.8-dev </p>

> $ sudo apt-get install python3.8-dev

<p><b> Bibliotecas do python: </b></p>

> $ pip3 install requests_html

> $ pip3 install lxml 

> $ pip3 install beautifulsoup4

<h2> Execução </h2>

<p> Para executar o programa, siga esses passos: </p>

1. Make

> $ make webScraping

2. Executar

> $ ./webScraping

* Comando extra

> $ make clean

<h2> Estrutura do Programa </h2>
<p> O programa está dividido em duas partes principais: o sistema de coleta e o sistema de gerenciamento das informações. O primeiro sistema foi implementado em python, enquanto o segundo em c++. A figura abaixo ilustra o funcionamento do sistema: </p>

![alt text](https://i.ibb.co/2tYRpVD/pasted-image-0.png "Figura 1")

<h3> Sistema de Gerenciamento </h3>
<p> O sistema de gerenciamento foi feito em C++. Ele é baseado na classe Product que guarda as informações mais relevantes do produto (seu nome, preço, url e a loja). Baseado nisso, o programa tem 5 funções principais. </p>

1. Busca por produto
<p> Nessa opção, o usuário irá entrar com um produto e uma faixa de preço. Essas informações serão passadas para o sistema de coleta (feito com o python3). Em seguida, o sistema de coleta irá retornar os resultados da busca para o programa gerenciador, no qual ele irá filtrar todos os dados e, por fim, irá retornar somente um único produto para o usuário. O resultado pode ser adicionado na lista de desejos. </p>

2. Ver lista de produtos
<p> Essa opção funciona de maneira similar a descrita anteriormente. A principal diferença é que, em vez do usuário fazer uma busca entre todas as lojas e receber somente um único resultado, ele irá buscar por um produto em uma loja específica e receberá várias resultados da pesquisa. O usuário poderá adicionar qualquer um dos resultados na lista de desejos. </p>

3. Configurar lojas
<p> Essa opção serve para que o usuário possa escolher quais são as lojas que serão utilizadas na busca do <b> item 1 </b>.</p>

4. Comparação de preços entre lojas
<p> Nessa opção, o usuário poderá comparar o preço de um produto entre 2 lojas. Cada loja irá retornar um resultado. Qualquer um dos dois resultados pode ser adicionado para a lista de desejos. </p>

5. Lista de desejos
<p> A lista de desejos é um local no qual o usuário poderá salvar produtos de seu interesse. Nessa opção, ele pode remover qualquer produto que não queira mais. A persistência dos dados será feita através do arquivo 'wishList.csv'. </p>
