## Animações
    Classes de desenho associadas a um objeto.
    As classes contém um método draw(MotionObject*) que aplica animação na posição e nas dimensões do objeto especificado.
    Quando o objeto é destruído a animação continua no estado do jogo e duas situações pode ocorrer:
        1. A animação pode estar ligada a outros objetos e continua sendo chamada
        2. A animação não está mais ligada a nenhum objeto e se torna obsoleta
    
    Na segunda situação seria interessante eliminar a animação antes do fim do jogo a fim de polpar recursos computacionais ?? Existira algum evento futuro no jogo que poderia chamar essa animação ??

    - Animation: classe base, desenha um frame único
    - AnimationFPS: classe derivada de Animation, desenha vários frames em taxa (FPS) especificada

    As Animações são atualizadas no update_game separadamente dos objetos animados. Não é o caso de atualizar as animações ao atualizar os objetos, embora isso seja mais intuitivo, se fosse feito, uma mesma animações poderia ser atualizada mais de uma vez no mesma iteração.
        Animation1 -> object1 object2 object3
            game loop
                object1.update()
                object2.update()
                object3.update()

            Animation1 seria atualizada 3 vezes

## Dúvida
    1. Como modelar a explosão ?
        Trata-se de uma animação temporária ou um objeto temporário ?
        Sendo um objeto temporário teria de derivar uma classe de MotionObject com tempo de vida. A vantagem seria que a combinação animação e comportamento é poderosa.
        Uma animação temporária teria de ser derivada de AnimationFPS ou Animation e teria de ter um retângulo com posição fixa. Para movimentá-la teria de adicionar um comportamento ?? Confuso. Sobreposição de ideias entre Animation e MotionObject.
        melho um objeto temporário então

        Como modelar um objeto temporário?
        A função update do objeto chama os comportamentos e também altera o born_time, caso o born_time seja igual ao end_time temos que deletar o objeto, como fazer isso? Temos que ser capazes de alterar o jogo de dentro de instâncias de MOtionObjects e classes filhas. Passamos um ponteiro Game* e armazenamos no estado de MotionObject.
        Na condição de destruição deletamos o objeto da lista de MotionObjects no jogo e deletamos do heap.

        Deletar:
            Alien:
                check condition?
                    remove this from game::motion_object_list
                    delete this (pointer para alien)

        Isso daria erro provavelmente
        O que faço ? armazeno o ponteiro para o alien em questão em uma lista de ponteiro no estado do jogo:
            ex.: delete_poninters = [p1, p2, p3...]
            Ao fim do loop chamo uma função de liberar memória
            deleto o objeto e a animação não é mais chamada
    
    2. O ponteiro Game* game é passado na construção de todos os MotionObjects, não teria uma forma de armazená-lo como statics atribute na classe MotionObject, de modo que todas as instâncias tenham acesso a ele e encurtando o construtor??