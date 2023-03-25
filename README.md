# Agenda-AED-I

Faça uma agenda capaz de incluir, apagar, buscar e listar
quantas pessoas o usuário desejar, porém, toda a informação
incluída na agenda deve ficar num único lugar chamado: “void
*pBuffer”.
Não pergunte para o usuário quantas pessoas ele vai incluir.
Não pode alocar espaço para mais pessoas do que o
necessário.
Cada pessoa tem nome[10], idade e telefone.

Continuar a sua implementação da agenda (exercício 3) semana 1 dentro dos mesmo parâmetros, mas incluir o seguinte.
Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. Todos os dados do programa devem ser guardados dentro do pBuffer.
Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer.
Exemplo do que não pode: int c; char a; int v[10];  void Funcao(int parametro)
Não pode usar struct em todo o programa.
Usar fila ordenada (heap) para armazenar as pessoas em ordem alfabética sempre que o usuário incluir uma nova pessoa.
Implementar a base de dados da agenda usando lista duplamente ligada
Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo.

Pbuffer Bytes : 1-4 = call;
                 5-14 = Nome para ser buscado;
                 15-24 = Nome;
                 25-28 = Idade;
                 29-32 = Telefone;
                 33-36 = Previous address // if sizeof(void *) = 4
                 37-40 = Next address // if sizeof(void *) = 4
