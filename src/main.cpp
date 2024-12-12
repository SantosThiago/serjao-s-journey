#include "PIG.h"
#define WIDTH 640
#define HEIGHT 480
#include <iostream>
using namespace std;

PIG_Evento evento;
PIG_Teclado meuTeclado;

struct a
{
    int x;
    int y;
    int obj;
    int peguei;
};

struct b
{
   int obj;
   int x;
   int y;
};

typedef struct elem{
    int vida;
    struct elem *prox;
}inimigo;

void AdicionaInimigo(inimigo **inicio,int vida){
    inimigo *novo=(inimigo *)malloc(sizeof(inimigo));
    if(*inicio==NULL){
        novo->vida=vida;
        novo->prox=NULL;
        *inicio=novo;
    }else{
        inimigo *aux=*inicio;
        while(aux->prox!=NULL){
            aux=aux->prox;
        }
        novo->vida=vida;
        novo->prox=NULL;
        aux->prox=novo;
    }
}

struct b criacoracao(int x,int y)
{
    int obj=CriaObjeto("../imagens/objetos/coracao.png",0);
    struct b coracao;
    coracao.x=x;
    coracao.y=y;
    coracao.obj=obj;
    SetDimensoesObjeto(obj,40,40);
    return coracao;
};

struct a criabanana(int x,int y)
{
    int obj=CriaObjeto("../imagens/objetos/banana.png",0);
    struct a banana;
    banana.x=x+50;
    banana.y=y+80;
    banana.obj=obj;
    SetDimensoesObjeto(obj,40,40);
    return banana;
}

void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }


    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';

    reverse(str, i);

    return str;
}

int main( int argc, char* args[] ){

    CriaJogo("Serjao's Journey",0,HEIGHT,WIDTH);
    inimigo *inimigo1=NULL;
    inimigo *inimigo2=NULL;
    inimigo *inimigo3=NULL;

    srand(time(NULL));
    bool direita = false;
    char str[10],str2[2],str3[10],str4[1000];
    char *historia[]={"Desde de pequeno","Serjao sempre quis mostrar seu valor para sua tribo.","Entao,ao chegar a idade adulta(3 anos)","decide começar sua jornada","Seu objetivo é enfrentar e caçar","o maior predador de sua especie,oncas.","E assim,Serjao partiu em busca de se tornar o MATADOR DE ONCAS."};
    int noar=0,vely=0,i,j,x=0,y=65,modo=-1,contbanana=0,contcoracao=3,morreu=0,menu=2,ressu=0,contkill=0,morto1=0,morto2=0,morto3=0;
    int perdeu=0,opcao=0,creditos=0,posx=480,posy=375,pos2x=140,pos2y=390,score=0,leaderboard=0,nodamage=1,aux=1,aux2=1;
    int tutorial=1,cena1=0,cena2=0,cena3=0,cena4=0,jogoroda=0,pause=0,soco,pulo;
    int x1 =0;
    int x2 =WIDTH;

    int timer=CriaTimer();
    int timer2=CriaTimer();
    int timer3=CriaTimer();
    int timer4=CriaTimer();
    int timerdano=CriaTimer();
    int timerpart=CriaTimer();
    int timerpart2=CriaTimer();
    int timertutorial=CriaTimer();
    int timercena1=CriaTimer();
    int timercena2=CriaTimer();
    int timercena3=CriaTimer();
    int timercena4=CriaTimer();

    int fonte1=CriaFonteNormal("../fontes/kongtext.ttf",25,AMARELO,1,PRETO);
    int fonte2=CriaFonteNormal("../fontes/OptimusPrinceps.ttf",45,VERMELHO,0,VERMELHO);
    int fonte3=CriaFonteNormal("../fontes/kongtext.ttf",25,BRANCO,0,BRANCO);
    int fonte4=CriaFonteNormal("../fontes/kongtext.ttf",15,BRANCO,0,BRANCO);
    int fonte5=CriaFonteNormal("../fontes/kongtext.ttf",20,AMARELO,1,PRETO);
    int fontehistoria=CriaFonteNormal("../fontes/kongtext.ttf",10,BRANCO,0,BRANCO);

    struct a vet[10];
    struct b vet2[3];

    int thanos=CriaVideo("../video/thanos.mp4");

    vet2[0]=criacoracao(0,445);
    vet2[1]=criacoracao(31,445);
    vet2[2]=criacoracao(62,445);

    int anima=CriaAnimacao("../imagens/gorila.png");
    int anima2=CriaAnimacao("../imagens/javali.png");
    int anima3=CriaAnimacao("../imagens/antilope.png");
    int macacodireita=CriaAnimacao("../imagens/macaquinho.png");
    int macacoesquerda=CriaAnimacao("../imagens/macaquinho2.png");
    int anima5=CriaAnimacao("../imagens/oncinha.png");
    int dancinha=CriaAnimacao("../imagens/dancinha.png");
    int dancinha2=CriaAnimacao("../imagens/dancinha.png");
    int dancinha3=CriaAnimacao("../imagens/dancinha.png");
    int dancinha4=CriaAnimacao("../imagens/dancinha.png");
    int dancinha5=CriaAnimacao("../imagens/dancinha.png");
    int dancinha6=CriaAnimacao("../imagens/dancinha.png");


    int bg1=CriaObjeto("../imagens/fundo.jpg",0);
    int bg2=CriaObjeto("../imagens/fundo.jpg",0);
    int obj1=CriaObjeto("../imagens/objetos/banana.png");
    int obj2=CriaObjeto("../imagens/carminha.jpg");
    int obj3=CriaObjeto("../imagens/objetos/continue.png");
    int obj4=CriaObjeto("../imagens/objetos/caveira.png");
    int obj5=CriaObjeto("../imagens/macacojoinha.png");
    int obj6=CriaObjeto("../imagens/tutorial.jpg",0,0);
    int obj7=CriaObjeto("../historia/1.jpg",0,0);
    int obj8=CriaObjeto("../historia/2.jpg",0,0);
    int obj9=CriaObjeto("../historia/3.jpg",0,0);
    int obj10=CriaObjeto("../historia/4.jpg",0,0);
    int op=CriaObjeto("../imagens/objetos/banana.png");
    int op2=CriaObjeto("../imagens/objetos/banana.png");
    int cred=CriaObjeto("../imagens/creditos.png",0,0);

    int audio1=CriaAudio("../audios/soco.mp3",0);
    int audio2=CriaAudio("../audios/pulo.mp3",0);
    int audio3=CriaAudio("../audios/hurt.wav",0);
    int audio4=CriaAudio("../audios/moeda.mp3",0);
    int audio5=CriaAudio("../audios/pedra.mp3",0);
    int audio6=CriaAudio("../audios/macaquinho.wav",0);
    int audio7=CriaAudio("../audios/inhaum.mp3",0);

    int ger=CriaGeradorParticulas(100,"../imagens/objetos/pedra.png",audio5);
    MudaDirecaoParticulas(ger,-210,-200);
    MoveGeradorParticulas(ger,posx,posy);
    int ger2=CriaGeradorParticulas(100,"../imagens/objetos/pedra.png",audio5);
    MudaDirecaoParticulas(ger2,200,-200);
    MoveGeradorParticulas(ger2,pos2x,pos2y);

    MoveAnimacao(anima3,150,80);
    MoveAnimacao(anima2,270,75);
    MoveAnimacao(macacoesquerda,90,360);
    MoveAnimacao(macacodireita,480,355);
    MoveAnimacao(anima5,550,70);
    MoveAnimacao(dancinha,100,65);
    MoveAnimacao(dancinha2,170,65);
    MoveAnimacao(dancinha3,360,65);
    MoveAnimacao(dancinha4,430,65);
    MoveAnimacao(dancinha5,85,360);
    MoveAnimacao(dancinha6,480,355);

    MoveObjeto(obj1,0,400);
    MoveObjeto(obj3,550,425);
    MoveObjeto(obj4,530,360);
    MoveObjeto(obj5,245,-10);
    MoveObjeto(op,210,246);
    MoveObjeto(op2,165,199);

    SetDimensoesObjeto(bg1, HEIGHT, WIDTH);
    SetDimensoesObjeto(bg2, HEIGHT, WIDTH);
    SetDimensoesObjeto(obj2,HEIGHT,WIDTH);
    SetDimensoesObjeto(obj7,HEIGHT,WIDTH);
    SetDimensoesObjeto(obj8,HEIGHT,WIDTH);
    SetDimensoesObjeto(obj9,HEIGHT,WIDTH);
    SetDimensoesObjeto(obj10,HEIGHT,WIDTH);
    SetDimensoesObjeto(cred,HEIGHT,WIDTH);
    SetDimensoesObjeto(obj1,40,40);
    SetDimensoesObjeto(obj3,50,50);
    SetDimensoesObjeto(obj4,100,100);
    SetDimensoesObjeto(obj5,300,500);
    SetDimensoesObjeto(op,30,30);
    SetDimensoesObjeto(op2,30,30);

    SetDimensoesAnimacao(anima3,80,80);
    SetDimensoesAnimacao(anima2,80,80);
    SetDimensoesAnimacao(anima,80,80);
    SetDimensoesAnimacao(macacoesquerda,80,80);
    SetDimensoesAnimacao(macacodireita,80,80);
    SetDimensoesAnimacao(anima5,80,80);
    SetDimensoesAnimacao(dancinha,80,80);
    SetDimensoesAnimacao(dancinha2,80,80);
    SetDimensoesAnimacao(dancinha3,80,80);
    SetDimensoesAnimacao(dancinha4,80,80);
    SetDimensoesAnimacao(dancinha5,80,80);
    SetDimensoesAnimacao(dancinha6,80,80);

    for (i=0;i<11;i++)
    {
        CriaModoAnimacao(anima,i,1);
        for(j=0;j<4;j++)
        {
            CriaFrameAnimacao(anima,i*4+j,43*j,42*i,42,43);
            if ((i==3 && j==1) || (i==2 && j==1))
            InsereFrameAnimacao(anima,i,i*4+j,0.01,audio1);
            else
            InsereFrameAnimacao(anima,i,i*4+j,0.1);
            if (i==5 && j==0 || (i==4 && j==0))
            InsereFrameAnimacao(anima,i,i*4+j,0.1,audio2);
            else
            InsereFrameAnimacao(anima,i,i*4+j,0.1);
            if (i==7 && j==0 || (i==6 && j==0))
            InsereFrameAnimacao(anima,i,i*4+j,0.1,audio3);
            else
            InsereFrameAnimacao(anima,i,i*4+j,0.1);
        }
    }

    for (i=0;i<6;i++)
    {
        CriaModoAnimacao(anima2,i,1);
        for(j=0;j<4;j++)
        {
            CriaFrameAnimacao(anima2,i*4+j,48*j,38*i,38,48);
            InsereFrameAnimacao(anima2,i,i*4+j,0.1);
        }
    }
    MudaModoAnimacao(anima2,1,1);
    for (i=0;i<8;i++)
    {
        CriaModoAnimacao(anima3,i,1);
        for (j=0;j<4;j++)
        {
            CriaFrameAnimacao(anima3,i*4+j,54*j,54*i,54,54);
            InsereFrameAnimacao(anima3,i,i*4+j,0.1);
        }
    }
    MudaModoAnimacao(anima3,2,1);

     for (i=0;i<1;i++)
    {
        CriaModoAnimacao(macacoesquerda,i,1);
        for(j=0;j<3;j++)
        {
            CriaFrameAnimacao(macacoesquerda,i*3+j,40*j,41*i,41,40);
            InsereFrameAnimacao(macacoesquerda,i,i*3+j,0.3);
        }
    }

    for (i=0;i<1;i++)
    {
        CriaModoAnimacao(macacodireita,i,1);
        for(j=0;j<3;j++)
        {
            CriaFrameAnimacao(macacodireita,i*3+j,40*j,41*i,41,40);
            InsereFrameAnimacao(macacodireita,i,i*3+j,0.3);
        }
    }

    for (i=0;i<10;i++)
    {
        CriaModoAnimacao(anima5,i,1);
        for(j=0;j<4;j++)
        {
            CriaFrameAnimacao(anima5,i*4+j,55*j,35*i,35,55);
            InsereFrameAnimacao(anima5,i,i*4+j,0.1);
        }
    }

    for (i=0;i<10;i++)
    {
        vet[i]=criabanana(rand() % HEIGHT, rand() % 100);
        MoveObjeto(vet[i].obj,vet[i].x,vet[i].y);
    }

    for(i=0;i<3;i++)
    {
        MoveObjeto(vet2[i].obj,vet2[i].x,vet2[i].y);
    }

    for (i=0;i<1;i++)
    {
        CriaModoAnimacao(dancinha,i,1);
        for (j=0;j<4;j++)
        {
            CriaFrameAnimacao(dancinha,i*4+j,43*j,42*i,42,43);
            InsereFrameAnimacao(dancinha,i,i*4+j,0.5);
        }
    }

    for (i=0;i<1;i++)
    {
        CriaModoAnimacao(dancinha2,i,1);
        for (j=0;j<4;j++)
        {
            CriaFrameAnimacao(dancinha2,i*4+j,43*j,42*i,42,43);
            InsereFrameAnimacao(dancinha2,i,i*4+j,0.5);
        }
    }

    for (i=0;i<1;i++)
    {
        CriaModoAnimacao(dancinha3,i,1);
        for (j=0;j<4;j++)
        {
            CriaFrameAnimacao(dancinha3,i*4+j,43*j,42*i,42,43);
            InsereFrameAnimacao(dancinha3,i,i*4+j,0.5);
        }
    }

    for (i=0;i<1;i++)
    {
        CriaModoAnimacao(dancinha4,i,1);
        for (j=0;j<4;j++)
        {
            CriaFrameAnimacao(dancinha4,i*4+j,43*j,42*i,42,43);
            InsereFrameAnimacao(dancinha4,i,i*4+j,0.5);
        }
    }

    for (i=0;i<1;i++)
    {
        CriaModoAnimacao(dancinha5,i,1);
        for (j=0;j<4;j++)
        {
            CriaFrameAnimacao(dancinha5,i*4+j,43*j,42*i,42,43);
            InsereFrameAnimacao(dancinha5,i,i*4+j,0.5);
        }
    }

    for (i=0;i<1;i++)
    {
        CriaModoAnimacao(dancinha6,i,1);
        for (j=0;j<4;j++)
        {
            CriaFrameAnimacao(dancinha6,i*4+j,43*j,42*i,42,43);
            InsereFrameAnimacao(dancinha6,i,i*4+j,0.5);
        }
    }

    CarregaBackground("../audios/consagrado8bits.mp3");
    PlayBackground(-1);

    meuTeclado = GetTeclado();

    while(JogoRodando()){
        evento = GetEvento();

     if (morto1==1 && morto2==1 && pause==0)
     {
        PlayAudio(audio7);
        SetVolume(audio7,1);
        pause=1;
     }

     if (evento.tipoEvento==EVENTO_TECLADO)
      {
        if (evento.teclado.acao==TECLA_PRESSIONADA)
        {
                if (evento.teclado.tecla==TECLA_p)
                        menu=1;

        }

      }

    if (TempoDecorrido(timer3) > 1.4 && jogoroda==1)
    {
        CriaParticula(ger2);
        ReiniciaTimer(timer3);
    }

     if (TempoDecorrido(timer4) > 1.4 && jogoroda==1)
    {
        CriaParticula(ger);
        ReiniciaTimer(timer4);
    }

    if (TempoDecorrido(timertutorial) > 5)
    {
        cena1=1;
        tutorial=0;
    }

    if (cena1==1 && TempoDecorrido(timercena1) > 15)
    {
        cena2=1;
        cena1=0;
    }

    if (cena2==1 && TempoDecorrido(timercena2) > 25)
    {
        cena3=1;
        cena2=0;
    }

    if (cena3==1 && TempoDecorrido(timercena3) > 35)
    {
        cena4=1;
        cena3=0;
    }

    if (cena4==1 && TempoDecorrido(timercena4) > 45)
    {
        menu=1;
        cena4=0;
    }

    if (nodamage==1 && aux==1)
    {
        score+=500;
        aux=0;
    }

    if (nodamage==0 && aux2==1)
    {
        aux2=0;
        score-=500;
    }

    if (menu==1)
    {
        if (evento.tipoEvento==EVENTO_TECLADO)
      {
        if (evento.teclado.acao==TECLA_PRESSIONADA)
        {
                if (evento.teclado.tecla==TECLA_BAIXO)
                    opcao=1;

                if (evento.teclado.tecla==TECLA_CIMA)
                    opcao=0;

                if (opcao==0 && evento.teclado.tecla==TECLA_ENTER)
                {
                    menu=0;
                    jogoroda=1;
                    CarregaBackground("../audios/trilhasonora.mp3");
                    PlayBackground(-1);
                }

                if (opcao==1 && evento.teclado.tecla==TECLA_ENTER)
                {
                    creditos=1;
                    CarregaBackground("../audios/consagrado.mp3");
                    PlayBackground(-1);
                    PlayVideo(thanos);
                }
        }
      }
    }

    if (contbanana==10)
        ressu=1;

    if (ColisaoParticulasAnimacao(ger,anima))
    {
        contcoracao--;
        score-=100;
        nodamage=0;
        PlayAudio(audio3);
    }
    if (ColisaoParticulasAnimacao(ger2,anima))
    {
        contcoracao--;
        score-=100;
        nodamage=0;
        PlayAudio(audio3);
    }
    if (ColisaoAnimacoes(anima,anima3) && TempoDecorrido(timerdano)>=5 && inimigo2->vida>0)
    {
        contcoracao--;
        score-=100;
        nodamage=0;
        PlayAudio(audio3);
    }
    if (ColisaoAnimacoes(anima,anima2) && TempoDecorrido(timerdano)>=5 && inimigo1->vida>0)
    {
        contcoracao--;
        score-=100;
        nodamage=0;
        PlayAudio(audio3);
    }
    if (ColisaoAnimacoes(anima,anima5) && TempoDecorrido(timerdano)>=5 && inimigo3->vida>0)
    {
        contcoracao--;
        score-=100;
        nodamage=0;
        PlayAudio(audio3);
    }

    if (TempoDecorrido(timerdano) > 5)
    {
        ReiniciaTimer(timerdano);
    }

    for (i=0;i<10;i++)
    {
         if (ColisaoAnimacaoObjeto(anima,vet[i].obj))
        {
            if (vet[i].peguei==0)
            {
                contbanana++;
                score+=50;
                PlayAudio(audio4);
            }
            vet[i].peguei=1;
        }
    }
        if(TempoDecorrido(timer) > 0.016){
            if(noar == 1){
                y = y + vely;
                vely = vely - 1;

                if(y <= 65){
                    y = 65;
                    noar = 0;
                }

            }
            ReiniciaTimer(timer);
        }
        MoveAnimacao(anima,x,y);

    AdicionaInimigo(&inimigo1,1);
    AdicionaInimigo(&inimigo2,2);
    AdicionaInimigo(&inimigo3,3);

     if (evento.tipoEvento==EVENTO_TECLADO)
    {
        if (evento.teclado.acao==TECLA_PRESSIONADA){
                if (evento.teclado.tecla==TECLA_ESQUERDA && jogoroda==1){
                    if (modo!=0)
                    {
                        MudaModoAnimacao(anima,0,1);
                        modo=0;
                    }
                    x-=10;
                }
                if (evento.teclado.tecla==TECLA_DIREITA && jogoroda==1){
                   if (modo!=1)
                   {
                       MudaModoAnimacao(anima,1,1);
                       modo=1;
                   }
                   x+=10;
                }

               if (evento.teclado.tecla==TECLA_z && jogoroda==1)
                {
                    if (modo==0 && pulo==1)
                    {
                        MudaModoAnimacao(anima,4,1);
                        noar=1;
                        vely=10;
                    }
                    else if(modo==1)
                    {
                        MudaModoAnimacao(anima,5,1);
                        noar=1;
                        vely=10;
                    }
                }

                if(evento.teclado.tecla==TECLA_a && ColisaoAnimacoes(anima,anima3))
        {
                        if (modo==0)
                        {
                            MudaModoAnimacao(anima,2,1);

                                if (inimigo2->vida>0)
                                    inimigo2->vida-=1;
                        }
                        else if (modo==1)
                        {
                            MudaModoAnimacao(anima,3,1);

                            if (inimigo2->vida>0)
                                inimigo2->vida-=1;
                        }

        }

              else if (evento.teclado.tecla==TECLA_a && ColisaoAnimacoes(anima,anima2))
        {
                        if (modo==0)
                        {
                            MudaModoAnimacao(anima,2,1);

                                if (inimigo1->vida>0)
                                    inimigo1->vida-=1;
                        }
                        else if (modo==1)
                        {
                            MudaModoAnimacao(anima,3,1);

                            if (inimigo1->vida>0)
                                inimigo1->vida-=1;
                        }

        }

                else if (evento.teclado.tecla==TECLA_a && ColisaoAnimacoes(anima,anima5))
        {
                        if (modo==0)
                        {
                            MudaModoAnimacao(anima,2,1);

                                if (inimigo3->vida!=0)
                                    inimigo3->vida-=1;

                        }
                        else if (modo==1)
                        {
                            MudaModoAnimacao(anima,3,1);

                            if (inimigo3->vida!=0)
                                inimigo3->vida-=1;
                        }

        }

                else if (evento.teclado.tecla==TECLA_a && jogoroda==1)
                {

                        if (modo==0)
                            MudaModoAnimacao(anima,2,1);

                        else if (modo==1)
                            MudaModoAnimacao(anima,3,1);

                }
                                                    }
    }

    if (inimigo1->vida<=0 && morto1!=1)
    {
        contkill++;
        morto1=1;
        score+=100;
    }
    if (inimigo2->vida<=0 && morto2!=1)
    {
        contkill++;
        morto2=1;
        score+=200;
    }
    if (inimigo3->vida<=0 && morto3!=1)
    {
        contkill++;
        morto3=1;
        score+=500;
        leaderboard=1;
        PausaTudo();
        PauseTudoAudio();
        PauseBackground();
    }
        if (contcoracao<1 && perdeu==1)
        {
            morreu=1;
            PausaTudo();
            PauseTudoAudio();
            PauseBackground();
        }

        else if(contbanana<10 && contcoracao<1)
        {
            morreu=1;
            PausaTudo();
            PauseTudoAudio();
            PauseBackground();
            MoveAnimacao(anima,0,0);
        }
        else if(contcoracao<1 && ressu==1)
        {
            perdeu=1;
            contcoracao=3;
        }
        else if(perdeu==1)
            ressu--;

        IniciaDesenho();

        if (tutorial==1 && morreu==0)
        {
            DesenhaObjeto(obj6);
            EscreverCentralizada("CONTROLES",300,450,fonte1);
            EscreverCentralizada("-> socar",370,390,fonte1);
            EscreverCentralizada("-> pular",370,300,fonte1);
            EscreverCentralizada("-> confirmar",370,210,fonte1);
            EscreverCentralizada("-> pular historia",370,120,fonte1);
            EscreverCentralizada("andar/selecionar opcao",390,50,fonte5);
        }

        if (cena1==1 &&  leaderboard==0 && morreu==0)
        {
            DesenhaObjeto(obj7);
            EscreverEsquerda(historia[0],0,40,fontehistoria);
             EscreverEsquerda(historia[1],0,20,fontehistoria);
        }

        if (cena2==1 &&  leaderboard==0  && morreu==0)
        {
            DesenhaObjeto(obj8);
            EscreverEsquerda(historia[2],0,40,fontehistoria);
            EscreverEsquerda(historia[3],0,20,fontehistoria);
        }

        if (cena3==1 &&  leaderboard==0 && morreu==0)
        {
            DesenhaObjeto(obj9);
            EscreverEsquerda(historia[4],0,40,fontehistoria);
            EscreverEsquerda(historia[5],0,20,fontehistoria);
        }

        if (cena4==1 && leaderboard==0 && morreu==0)
        {
            DesenhaObjeto(obj10);
            EscreverEsquerda(historia[6],0,20,fontehistoria);
        }

        if (menu==1 && jogoroda==0)
        {
        if (creditos==0)
        {
                DesenhaObjeto(bg2);
                DesenhaAnimacao(dancinha);
                DesenhaAnimacao(dancinha2);
                DesenhaAnimacao(dancinha3);
                DesenhaAnimacao(dancinha4);
                DesenhaAnimacao(dancinha5);
                DesenhaAnimacao(dancinha6);
                EscreverCentralizada("SERJAO'S",313,400,fonte1);
                EscreverCentralizada("JOURNEY",313,350,fonte1);
                EscreverCentralizada("JOGAR",300,250,fonte1);
                EscreverCentralizada("CREDITOS",300,200,fonte1);
        }
        if (opcao==0 && creditos!=1)
            DesenhaObjeto(op);

        if (opcao==1 && creditos !=1)
                DesenhaObjeto(op2);

        else if (creditos==1)
                    {
                        DesenhaObjeto(cred);
                        DesenhaVideo(thanos);
                        EscreverCentralizada("CREDITOS",300,450,fonte3);
                        EscreverEsquerda("Thiago dos Santos",0,420,fonte4);
                        EscreverEsquerda("Luan Freire",0,390,fonte4);
                        EscreverEsquerda("Felipe Peixoto",0,360,fonte4);
                    }
        }

else if (morreu!=1 && leaderboard!=1 && jogoroda==1)
    {
        DesenhaObjeto(bg1);
        DesenhaObjeto(obj3);
        DesenhaObjeto(obj4);
        MoveParticulas(ger);
        DesenhaParticulas(ger);
        MoveParticulas(ger2);
        DesenhaParticulas(ger2);

        for (i=0;i<contcoracao;i++)
        {
            DesenhaObjeto(vet2[i].obj);
        }

        DesenhaObjeto(obj1);

        for (i=0;i<10;i++)
        {
            if (vet[i].peguei!=1)
            DesenhaObjeto(vet[i].obj);
        }

        EscreverEsquerda(itoa(contbanana,str,10),45,410,fonte1);
        EscreverDireita(itoa(ressu,str2,10),620,440,fonte1);
        EscreverDireita(itoa(contkill,str3,10),620,400,fonte1);
        EscreverCentralizada("score",300,440,fonte1);
        EscreverCentralizada(itoa(score,str4,10),300,420,fonte1);

        DesenhaAnimacao(anima);
        DesenhaAnimacao(macacoesquerda);
        DesenhaAnimacao(macacodireita);

        if (inimigo1->vida>=1)
             DesenhaAnimacao(anima2);
        if (inimigo2->vida>=1)
            DesenhaAnimacao(anima3);
        if (inimigo3->vida>=1)
        DesenhaAnimacao(anima5);
    }

 else if (leaderboard==1)
 {
        EscreverCentralizada("SCORE",300,450,fonte3);
        EscreverCentralizada(itoa(score,str4,10),300,410,fonte3);
        EscreverCentralizada("VOCE VENCEU",300,300,fonte3);
        DesenhaObjeto(obj5);
 }

else if (morreu==1)
{
    DesenhaObjeto(obj2);
    EscreverCentralizada("VOCE MORREU",300,100,fonte2);
}
        EncerraDesenho();
    }
    FinalizaJogo();

    FILE *arq=fopen("recordes.txt","a+");
    fprintf(arq,"%d\n",score);
    fclose(arq);
    return 0;
}
