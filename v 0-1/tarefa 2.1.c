void statust (int x){
	//printf("\ndigite 1 para 'parado'\ndigite 2 para 'em andamento'\ndigite 3 para 'finalizado'\nopção: ");
	//scanf("%d", &statust);
	switch (x) {//função utilizada para facilitar os inputs do status da tarefa para o usuário
	case 1:
		return("parado");
	case 2:
		return("em andamento");
	case 3:
		return("finalizado");
	};
};

typedef struct Tarefa{//Luiz está finalizando esse struct
	int tipo;
	struct task *anterior;
	struct task *proxima;
	char desc[261];
	usuario responsavel;//marcador de quem pegou a tarefa
	int marcador_responsavel;//marcador de conclusão
	int marcador_dono;//marcardo de certificaçnao de conclusão
	char descricaot[260];	
	char titulot[51];
	char funcionariot[51];	
	void statust(int x);	
	int deadlinet;
	int tempoet;
	int deadlinert = deadlinet - tempoet
}tarefa;
