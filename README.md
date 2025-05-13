# Trabalho 1 – Sistemas Operacionais

## Assunto
Este trabalho aborda simulações e implementações envolvendo algoritmos de escalonamento de processos, sincronização de threads em ambientes com recursos limitados e controle de acesso concorrente utilizando técnicas de sincronização clássicas. As atividades estão divididas em três questões, cada uma com foco em um aspecto fundamental de sistemas operacionais.

## Professor
Prof. Daniel Silva Ferreira

## Equipe
- Arthur Dantas Lacerda Silva Patrício (Questão 1)
- Bruno Costa Diniz Leandro (Questão 1)
- Guilherme Amaro Clarindo (Questão 2)
- Rafael Jorge Cabral Cardoso (Questão 3)

## Questão 1 – Simulação de Algoritmos de Escalonamento

### Objetivo
Comparar o desempenho do algoritmo Round Robin (RR) com diferentes valores de quantum, em relação aos algoritmos FCFS (First Come, First Served) e SJF (Shortest Job First) não preemptivo.

### Detalhes
- Geração de N processos com tempos de chegada e burst time distintos.
- Métricas analisadas:
  - Tempo médio de espera (± desvio padrão)
  - Tempo médio de retorno (± desvio padrão)
  - Vazão do sistema
- Mudança de contexto consome 1 unidade de tempo.
- Simulação exibirá a sequência de execução dos processos para cada algoritmo.

---

## Questão 2 – Sincronização em Ambiente com Recursos Compartilhados

### Objetivo
Simular um cenário com 5 programadores que compartilham recursos limitados: um compilador exclusivo e um banco de dados com acesso simultâneo limitado a 2 programadores.

### Regras
- Apenas um programador pode usar o compilador por vez.
- Máximo de dois programadores acessando o banco de dados simultaneamente.
- Um programador só pode iniciar a compilação se tiver acesso aos dois recursos.
- O sistema deve evitar deadlocks e inanição.

### Requisitos
Implementação com técnicas de sincronização adequadas (semaphores, mutexes, etc.), garantindo segurança e eficiência no uso dos recursos compartilhados.

---

## Questão 3 – Controle de Acesso à Sala de Repouso

### Objetivo
Implementar uma lógica de controle de acesso a uma sala de repouso em um hospital veterinário com as seguintes condições:

- Cachorros podem entrar se não houver gatos.
- Gatos podem entrar se não houver cachorros.
- A sala pode estar nos estados: Vazia, Cachorros Presentes, Gatos Presentes.

### Funções a serem implementadas
- `dogWantsToEnter`
- `catWantsToEnter`
- `dogLeaves`
- `catLeaves`

### Requisitos
Utilização de técnicas de sincronização apropriadas para garantir a exclusão mútua entre os tipos de animais, evitando condições de corrida e mantendo a justiça no acesso.

