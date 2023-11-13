# Autómato celular - C
## Descrição
Essa é uma simulação de um ecossistema simples, habitado por duas espécies de animais, raposas e coelhos, cuja existência ao longo de gerações é mutuamente dependente.
## Regras para os coelhos
- Os coelhos podem se mover horizontalmente ou verticalmente (ou seja, norte, leste, sul e oeste), mas não na diagonal.
- Em cada geração, os coelhos tentam se mover para uma célula adjacente vazia. Se houver muitas células adjacentes vazias, eles escolherão uma de acordo com um critério comum para selecionar células adjacentes (veja abaixo). Se não houver célula adjacente vazia, eles permanecerão no mesmo local.
- Os coelhos podem procriar sempre que **RABBITS_BREEDING_TIME** gerações se passaram desde que nasceram ou desde a última procriação. Sempre que um coelho atinge essa idade (para procriar) e faz um movimento, deixa em sua última posição um novo coelho e a idade de procriação de ambos os coelhos é definida como zero.
Regras para as raposas
- As raposas podem se mover horizontalmente ou verticalmente, mas não na diagonal.
- Em cada geração, as raposas tentam comer um coelho movendo-se para uma célula adjacente que é ocupada por um coelho. Se houver muitas células adjacentes ocupadas com coelhos, eles escolherão uma de acordo com os critérios comuns para selecionar células adjacentes (veja abaixo). Se não houver célula adjacente ocupada por um coelho, as raposas tentam se mover para uma célula adjacente vazia, seguindo os mesmos critérios. Se não houver uma célula adjacente ocupada com um coelho ou vazia, elas permanecerão no mesmo local.
- As raposas morrem de fome sempre que **FOXES_STARVING_TIME** gerações se passaram desde que nasceram ou desde a última vez que comeram um coelho. As raposas morrem depois de não encontrar um coelho para comer e antes de tentar se mover para uma célula adjacente vazia.
- As raposas podem procriar sempre que **FOXES_BREEDING_TIME** gerações se passaram desde que nasceram ou desde a última vez que foram criadas. Sempre que uma raposa atinge essa idade (para procriar) e faz um movimento, deixa em sua última posição uma nova raposa e a idade de procriação de ambas as raposas é definida como zero.

## Regras para as rochas
- As rochas não se mexem e nenhum animal pode ocupar seu espaço.

## Critérios para seleção de células adjacentes
- Seguindo o sentido horário, comece a numerar, a partir de 0, as P possíveis células para onde uma raposa/coelho pode se mover (células adjacentes ao norte, leste, sul e oeste).
- Seja G a geração atual e (X, Y) as coordenadas das células onde uma raposa/coelho está posicionada no espaço do ecossistema, então a célula adjacente a ser escolhida é determinada por (G + X + Y) mod P. Suponha que a geração inicial é a 0 e a origem do mundo é (0,0).

## Entrada e saida
A aplicação aceita como entrada um arquivo com os parâmetros de configuração e a descrição do estado inicial do ecossistema. Esta descrição segue o seguinte padrão: a primeira linha de entrada possui todos os parâmetros de configuração (incluindo um número inteiro SO representando o número de objetos no ecossistema inicial), seguido por L linhas, cada uma representando um objeto do ecossistema inicial. Os parâmetros de configuração são os seguintes (em ordem):

- **RABBITS_BREEDING_TIME:** Número de gerações até que um coelho possa procriar
- **FOXES_STARVING_TIME:** Número de gerações até que uma raposa possa procriar
- **FOXES_BREEDING_TIME:** Número de gerações para uma raposa morrer de fome
- **NUM_GENERATIONS:** Número de gerações para a simulação
- **L:** Número de linhas da matriz representando o ecossistema
- **C:** Número de colunas da matriz representando o ecossistema
- **SO:** Número de objetos no ecossistema inicial

Os objetos no ecossistema inicial são fornecidos usando o formato OBJETO X Y, em que OBJETO pode ser ROCHA, RAPOSA ou COELHO, e X e Y são as coordenadas em que o OBJETO está posicionado na matriz. Um exemplo de entrada é:

> 2 4 3 6 5 5 9
ROCHA 0 0
COELHO 0 2
RAPOSA 0 4
RAPOSA 1 0
RAPOSA 1 4
ROCHA 2 4
COELHO 3 0
COELHO 4 0
RAPOSA 4 4

A aplicação deve escrever na saída padrão a descrição do estado final do ecossistema, seguindo o mesmo formato usado para a entrada. Para o exemplo dado, a saída deve ser:

> 2 4 3 0 5 5 5
ROCHA 0 0
ROCHA 2 4
COELHO 3 0
RAPOSA 4 0
RAPOSA 4 3

Mais detalhadamente, para o exemplo dado, a sequência de gerações é a seguinte:

| Gen 0 | Gen 1 | Gen 2 | Gen 3 | Gen 4 | Gen 5 | Gen 6 |
|-------|-------|-------|-------|-------|-------|-------|
| * C R | *C R  | * R   | * R   | * R   | *     | *     |
| R R   | R     | R     |       |       |       |       |
| *     | R *   | *     | *     | *     | *     | *     |
| C     | C R   | R     |       | C     | C     | C     |
| C R   | C     | C R   | R CC  | R C   | RR    | R R   |

No exemplo acima, * é uma rocha, C um coelho e R raposa. O arquivo de entrada deve ser lido da entrada padrão, e os resultados devem ser impressos na saída padrão.


# Cellular Automaton - C
## Description
This is a simulation of a simple ecosystem, inhabited by two species of animals, foxes and rabbits, whose existence over generations is mutually dependent.

## Rules for Rabbits
- Rabbits can move horizontally or vertically (i.e., north, east, south, and west), but not diagonally.
In each generation, rabbits attempt to move to an adjacent empty cell. If there are many adjacent empty cells, they will choose one according to a common criterion for selecting adjacent cells (see below). If there is no adjacent empty cell, they remain in the same location.
- Rabbits can breed whenever **RABBITS_BREEDING_TIME** generations have passed since they were born or since the last breeding. Whenever a rabbit reaches this age (for breeding) and makes a move, it leaves a new rabbit in its last position, and the breeding age of both rabbits is set to zero.

## Rules for Foxes
- Foxes can move horizontally or vertically, but not diagonally.
In each generation, foxes attempt to eat a rabbit by moving to an adjacent cell occupied by a rabbit. If there are many adjacent cells occupied by rabbits, they will choose one according to common criteria for selecting adjacent cells (see below). If there is no adjacent cell occupied by a rabbit, foxes attempt to move to an adjacent empty cell, following the same criteria. If there is no adjacent cell occupied by a rabbit or empty, they remain in the same location.
- Foxes starve whenever **FOXES_STARVING_TIME** generations have passed since they were born or since the last time they ate a rabbit. Foxes die after not finding a rabbit to eat and before attempting to move to an adjacent empty cell.
- Foxes can breed whenever **FOXES_BREEDING_TIME** generations have passed since they were born or since the last time they were created. Whenever a fox reaches this age (for breeding) and makes a move, it leaves a new fox in its last position, and the breeding age of both foxes is set to zero.

## Rules for Rocks
- Rocks do not move, and no animal can occupy their space.

## Criteria for selecting adjacent cells
- Clockwise, start numbering, starting from 0, the P possible cells to which a fox/rabbit can move (cells adjacent to the north, east, south, and west).
- Let G be the current generation and (X, Y) be the coordinates of the cells where a fox/rabbit is positioned in the ecosystem space, then the adjacent cell to be chosen is determined by (G + X + Y) mod P. Suppose the initial generation is 0, and the origin of the world is (0,0).

## Input and Output
The application accepts as input a file with the configuration parameters and the description of the initial state of the ecosystem. This description follows the following pattern: the first input line has all the configuration parameters (including an integer SO representing the number of objects in the initial ecosystem), followed by L lines, each representing an object in the initial ecosystem. The configuration parameters are as follows (in order):

- **RABBITS_BREEDING_TIME:** Number of generations until a rabbit can breed
- **FOXES_STARVING_TIME:** Number of generations until a fox can breed
- **FOXES_BREEDING_TIME:** Number of generations for a fox to starve
- **NUM_GENERATIONS:** Number of generations for the simulation
- **L:** Number of rows in the matrix representing the ecosystem
- **C:** Number of columns in the matrix representing the ecosystem
- **SO:** Number of objects in the initial ecosystem

Objects in the initial ecosystem are provided using the format OBJECT X Y, where OBJECT can be ROCK, FOX, or RABBIT, and X and Y are the coordinates where the OBJECT is positioned in the matrix. An example input is:

> 2 4 3 6 5 5 9
ROCHA 0 0
COELHO 0 2
RAPOSA 0 4
RAPOSA 1 0
RAPOSA 1 4
ROCHA 2 4
COELHO 3 0
COELHO 4 0
RAPOSA 4 4

The application should write to the standard output the description of the final state of the ecosystem, following the same format used for input. For the given example, the output should be:

> 2 4 3 0 5 5 5
ROCHA 0 0
ROCHA 2 4
COELHO 3 0
RAPOSA 4 0
RAPOSA 4 3

In more detail, for the given example, the sequence of generations is as follows:

| Gen 0 | Gen 1 | Gen 2 | Gen 3 | Gen 4 | Gen 5 | Gen 6 |
|-------|-------|-------|-------|-------|-------|-------|
| * C R | *C R  | * R   | * R   | * R   | *     | *     |
| R R   | R     | R     |       |       |       |       |
| *     | R *   | *     | *     | *     | *     | *     |
| C     | C R   | R     |       | C     | C     | C     |
| C R   | C     | C R   | R CC  | R C   | RR    | R R   |

In the example above, * is a rock, C a rabbit, and R a fox. The input file should be read from the standard input, and the results should be printed to the standard output.