int main() {
    char linhaComando[512];

    tUsuario **usuarios = NULL;
    int qtdUsuarios = 0;
    tDistribuidor **distribuidores = NULL;
    int qtdDistribuidores = 0;
    tConteudo **conteudos = NULL;
    int qtdConteudos = 0;

    // O loop principal lê a linha do COMANDO
    while (fgets(linhaComando, sizeof(linhaComando), stdin) != NULL) {
        linhaComando[strcspn(linhaComando, "\n")] = '\0';
        if (strcmp(linhaComando, "OUT") == 0) {
            break;
        }

        // strtok modifica a string, então fazemos uma cópia para preservar os argumentos originais se necessário
        char copiaLinhaComando[512];
        strcpy(copiaLinhaComando, linhaComando);
        char *comando = strtok(copiaLinhaComando, " ");
        char *args = strtok(NULL, "");

        if (strcmp(comando, "CAT") == 0) {
            // Comandos CAT e CAC precisam ler uma linha de dados adicional
            char linhaDados[512];
            if (fgets(linhaDados, sizeof(linhaDados), stdin) == NULL) break;
            linhaDados[strcspn(linhaDados, "\n")] = '\0';

            char *tipo_ator_str = strtok(args, " ");
            char *subtipo_str = strtok(NULL, "");

            if (strcmp(tipo_ator_str, "USUARIO") == 0) {
                char copiaDados[512];
                strcpy(copiaDados, linhaDados);
                strtok(copiaDados, ";"); // Pula nome
                char* cpf = strtok(NULL, ";");

                int jaExiste = 0;
                for (int i = 0; i < qtdUsuarios; i++) {
                    if (strcmp(getCpfUsuario(usuarios[i]), cpf) == 0) {
                        printf("CPF JA EXISTENTE! OPERACAO NAO PERMITIDA!\n");
                        jaExiste = 1;
                        break;
                    }
                }

                if (!jaExiste) {
                    TipoUsuario tipo = (strcmp(subtipo_str, "INFANTIL") == 0) ? INFANTIL : ADULTO;
                    TipoAssinatura assinatura = (strcmp(subtipo_str, "PREMIUM") == 0) ? PREMIUM : PADRAO;
                    
                    qtdUsuarios++;
                    usuarios = realloc(usuarios, qtdUsuarios * sizeof(tUsuario*));
                    usuarios[qtdUsuarios - 1] = criaUsuario(tipo, assinatura, linhaDados);
                    printf("USUARIO CADASTRADO COM SUCESSO!\n");
                }

            } else if (strcmp(tipo_ator_str, "DISTRIBUIDOR") == 0) {
                char copiaDados[512];
                strcpy(copiaDados, linhaDados);
                strtok(copiaDados, ";"); // Pula nome
                char* cnpj = strtok(NULL, ";");
                
                int jaExiste = 0;
                for (int i = 0; i < qtdDistribuidores; i++) {
                    if (strcmp(getCnpjDistribuidor(distribuidores[i]), cnpj) == 0) {
                        printf("CNPJ JA EXISTENTE! OPERACAO NAO PERMITIDA!\n");
                        jaExiste = 1;
                        break;
                    }
                }

                if (!jaExiste) {
                    qtdDistribuidores++;
                    distribuidores = realloc(distribuidores, qtdDistribuidores * sizeof(tDistribuidor*));
                    distribuidores[qtdDistribuidores - 1] = criaDistribuidor(linhaDados);
                    printf("DISTRIBUIDOR CADASTRADO COM SUCESSO!\n");
                }
            }
        } 
        else if (strcmp(comando, "CAC") == 0)
        {
            char linhaDados[512];
            if (fgets(linhaDados, 512, stdin) == NULL)
            {
                break;
            }
            linhaDados[strcspn(linhaDados, "\n")] = '\0';

            char copiaLinhaDados[512];
            strcpy(copiaLinhaDados, linhaDados);

            char *tipoConteudoStr = strtok(copiaLinhaDados, ";");
            char *idConteudo = strtok(NULL, ";");
            char tipo = tipoConteudoStr[0];

            int id_existente = 0;
            for (int i = 0; i < qtdConteudos; i++)
            {
                if (strcmp(getCodConteudo(conteudos[i]), idConteudo) == 0)
                {
                    id_existente = 1;
                    break;
                }
            }

            if (id_existente)
            {
                if (tipo == 'S')
                {
                    printf("SERIE ATUALIZADA COM SUCESSO!\n");
                }
                else
                {
                    printf("CONTEUDO JA CADASTRADO! OPERACAO NAO PERMITIDA!\n");
                }
            }
            else
            {
                char *dadosParaCriacao = strchr(linhaDados, ';');
                if (dadosParaCriacao != NULL)
                {
                    dadosParaCriacao++;
                }

                void *dadoEspecifico = NULL;
                if (tipo == 'F')
                    dadoEspecifico = criaFilme(dadosParaCriacao);
                else if (tipo == 'S')
                    dadoEspecifico = criaSerie(dadosParaCriacao);
                else if (tipo == 'J')
                    dadoEspecifico = criaJogo(dadosParaCriacao);

                if (dadoEspecifico != NULL)
                {
                    tConteudo *novoConteudo = NULL;
                    if (tipo == 'F')
                    {
                        novoConteudo = criaConteudo(dadoEspecifico, getAnoLancamentoFilme, getCodConteudoFilme, getNotaMediaFilme, getTituloFilme, getDuracaoFilme, printaFilme, getRestricaoAssinaturaFilme, getTipoFilme, getRestricaoIdadeFilme, liberaFilme);
                    }
                    else if (tipo == 'S')
                    {
                        novoConteudo = criaConteudo(dadoEspecifico, getAnoLancamentoSerie, getCodConteudoSerie, getNotaMediaSerie, getTituloSerie, getDuracaoPorEpisodioSerie, NULL, getRestricaoAssinaturaSerie, getTipoSerie, getRestricaoIdadeSerie, liberaSerie);
                    }
                    else if (tipo == 'J')
                    {
                        novoConteudo = criaConteudo(dadoEspecifico, getAnoLancamentoJogo, getCodJogo, getNotaMediaJogo, getTituloJogo, getDuracaoEstimadaJogo, NULL, getRestricaoAssinaturaJogo, getTipoJogo, getRestricaoIdadeJogo, liberaJogo);
                    }

                    qtdConteudos++;
                    conteudos = realloc(conteudos, qtdConteudos * sizeof(tConteudo *));
                    conteudos[qtdConteudos - 1] = novoConteudo;
                    printf("CONTEUDO CADASTRADO COM SUCESSO!\n");
                }
            }
        }
        else if (strcmp(comando, "ACL") == 0)
        {
            char *cpfUsuario = strtok(args, " ");
            char *idConteudo = strtok(NULL, "");

            tUsuario *usuarioAlvo = NULL;
            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            tConteudo *conteudoAlvo = NULL;
            if (usuarioAlvo != NULL)
            {
                for (int i = 0; i < qtdConteudos; i++)
                {
                    if (strcmp(getCodConteudo(conteudos[i]), idConteudo) == 0)
                    {
                        conteudoAlvo = conteudos[i];
                        break;
                    }
                }
            }

            if (usuarioAlvo != NULL && conteudoAlvo != NULL)
            {
                adicionaConteudoNaLista(usuarioAlvo, conteudoAlvo);
                imprimeListaDeReproducao(usuarioAlvo);
            }
            else if (usuarioAlvo == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
            else
            {
                printf("O CONTEUDO %s NAO ESTA CADASTRADO!\n", idConteudo);
            }
        }
        else if (strcmp(comando, "RCL") == 0)
        {
            char *cpfUsuario = strtok(args, " ");
            char *idConteudo = strtok(NULL, "");

            tUsuario *usuarioAlvo = NULL;
            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            if (usuarioAlvo != NULL)
            {
                if (removeConteudoDaLista(usuarioAlvo, idConteudo))
                {
                    printf("O CONTEUDO %s FOI REMOVIDO DA LISTA DE REPRODUCAO DO USUARIO %s!\n", idConteudo, cpfUsuario);
                }
                else
                {
                    printf("O CONTEUDO NAO ESTA PRESENTE NA LISTA DE REPRODUCAO DO USUARIO %s!\n", cpfUsuario);
                }
                imprimeListaDeReproducao(usuarioAlvo);
            }
            else
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
        }
        else if (strcmp(comando, "MLR") == 0)
        {
            char *cpfUsuario = strtok(args, " ");

            tUsuario *usuarioAlvo = NULL;
            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            if (usuarioAlvo != NULL)
            {
                imprimeListaDeReproducao(usuarioAlvo);
            }
            else
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
        }
        else if (strcmp(comando, "CPCLR") == 0)
        {
            char *cpfUsuario = strtok(args, " ");
            tUsuario *usuarioAlvo = NULL;
            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            if (usuarioAlvo == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
            else if (getQtdConteudoNaLista(usuarioAlvo) == 0)
            {
                printf("LISTA DO USUARIO %s ESTA VAZIA! OPERACAO NAO PERMITIDA!\n", cpfUsuario);
            }
            else
            {
                tConteudo *conteudoConsumido = consomePrimeiroDaLista(usuarioAlvo);

                printf("CONTEUDO %s FOI CONSUMIDO PELO USUARIO %s!\n", getTituloConteudo(conteudoConsumido), cpfUsuario);

                if (getTipoUsuario(usuarioAlvo) == ADULTO)
                {
                    printf("DIGITE UMA NOTA ENTRE 1 E 5\n");
                    char linhaNota[10];
                    fgets(linhaNota, 10, stdin);
                    int nota = atoi(linhaNota);

                    if (nota >= 1 && nota <= 5)
                    {
                        tAvaliacao *novaAvaliacao = criaAvaliacao(cpfUsuario, nota);
                        inserirAvaliacaoConteudo(conteudoConsumido, novaAvaliacao);
                        printf("CONTEUDO %s AVALIADO COM NOTA %d!\n", getTituloConteudo(conteudoConsumido), nota);
                    }
                }
            }
        }
        else if (strcmp(comando, "RGC") == 0)
        {
            char *cpfUsuario = strtok(args, " ");
            tUsuario *usuarioAlvo = NULL;

            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            if (usuarioAlvo != NULL)
            {
                printf("RELATORIO GERAL DE CONTEUDO\n");
                int contadorImpressao = 0;
                TipoUsuario tipoUsuario = getTipoUsuario(usuarioAlvo);
                TipoAssinatura assinaturaUsuario = getAssinaturaUsuario(usuarioAlvo);

                for (int i = 0; i < qtdConteudos; i++)
                {
                    tConteudo *conteudoAtual = conteudos[i];
                    int podeImprimir = 1;

                    if (assinaturaUsuario == PADRAO && getRestricaoConteudo(conteudoAtual) == PREMIUM)
                    {
                        podeImprimir = 0;
                    }
                    if (tipoUsuario == INFANTIL && getRestricaoIdade(conteudoAtual) == ADULTO)
                    {
                        podeImprimir = 0;
                    }

                    if (podeImprimir)
                    {
                        contadorImpressao++;
                        printf("%d-", contadorImpressao);
                        printaConteudo(conteudoAtual);
                    }
                }

                if (contadorImpressao == 0)
                {
                    printf("NENHUM CONTEUDO ENCONTRADO!\n");
                }
            }
            else
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
        }
        else if (strcmp(comando, "GRU") == 0)
        {
            char *cpfUsuario = strtok(args, " ");
            tUsuario *usuarioAlvo = NULL;

            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            if (usuarioAlvo == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
            else
            {
                printf("DIGITE A SENHA:\n");
                char senhaDigitada[50];
                fgets(senhaDigitada, 50, stdin);
                senhaDigitada[strcspn(senhaDigitada, "\n")] = '\0';

                if (strcmp(getSenhaUsuario(usuarioAlvo), senhaDigitada) != 0)
                {
                    printf("SENHA INCORRETA! OPERACAO NAO PERMITIDA!\n");
                }
                else
                {
                    printf("RELATORIO USUARIO DE CPF %s\n", getCpfUsuario(usuarioAlvo));
                    printf("NOME: %s\n", getNomeUsuario(usuarioAlvo));
                    printf("TELEFONE: %s\n", getTelefoneUsuario(usuarioAlvo));
                    printf("ENDERECO: %s\n", getEnderecoUsuario(usuarioAlvo));
                    printf("NOME DE USUARIO: %s\n", getUsernameUsuario(usuarioAlvo));

                    printf("SENHA: ");
                    for (int i = 0; i < strlen(getSenhaUsuario(usuarioAlvo)); i++)
                    {
                        printf("*");
                    }
                    printf("\n");

                    printf("E-MAIL: %s\n", getEmailUsuario(usuarioAlvo));
                    printf("DATA NASCIMENTO: %s\n", getDataNascimentoUsuario(usuarioAlvo));
                    printf("NUM. CONTEUDOS CONSUMIDOS: %d\n", getNumProdutosConsumidosUsuario(usuarioAlvo));

                    int totalMinutos = getTotalMinutosConsumidosUsuario(usuarioAlvo);
                    int horas = 0;
                    int minutos = 0;
                    converteMinutos(totalMinutos, &horas, &minutos);
                    printf("TOTAL HORAS CONSUMIDAS: %02d:%02d\n", horas, minutos);

                    printf("NUM. AVALIACOES REALIZADAS: %d\n", getNumAvaliacoesRealizadasUsuario(usuarioAlvo));

                    if (getTipoUsuario(usuarioAlvo) == ADULTO)
                    {
                        printf("USUARIO 18+ %s\n", getAssinaturaUsuario(usuarioAlvo) == PREMIUM ? "PREMIUM" : "PADRAO");
                        printf("CARTAO NUM.: %s\n", getCartaoDeCreditoUsuario(usuarioAlvo));
                    }
                    else
                    {
                        printf("USUARIO INFANTIL %s\n", getAssinaturaUsuario(usuarioAlvo) == PREMIUM ? "PREMIUM" : "PADRAO");
                        printf("CPF RESPONSAVEL: %s\n", getCpfResponsavelUsuario(usuarioAlvo));
                    }

                    imprimeListaDeReproducao(usuarioAlvo);

                    printf("LISTA DE CONTEUDOS CONSUMIDOS:\n");
                    imprimeListaDeConsumidos(usuarioAlvo);
                }
            }
        }
        else if (strcmp(comando, "COF") == 0 || strcmp(comando, "COFP") == 0)
        {
            char *cpfUsuario = strtok(args, " ");
            char *termoBusca = strtok(NULL, "");

            tUsuario *usuarioAlvo = NULL;
            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            if (usuarioAlvo == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
            else
            {
                TipoAssinatura assinaturaUsuario = getAssinaturaUsuario(usuarioAlvo);
                TipoUsuario tipoUsuario = getTipoUsuario(usuarioAlvo);

                if (strcmp(comando, "COFP") == 0 && assinaturaUsuario == PADRAO)
                {
                    printf("A CONTA DE CPF %s NAO POSSUI PERMISSAO PARA EXECUTAR ESSE COMANDO!\n", cpfUsuario);
                }
                else
                {
                    printf("# - TIPO ID; NOME; DURACAO; DISP. IDIOMA; ANO; PRODUTORA\n");
                    int contadorImpressao = 0;

                    for (int i = 0; i < qtdConteudos; i++)
                    {
                        tConteudo *conteudoAtual = conteudos[i];
                        if (getTipoConteudo(conteudoAtual) != 'F')
                        {
                            continue;
                        }

                        int podeImprimir = 1;
                        if (strcmp(comando, "COF") == 0 && getRestricaoConteudo(conteudoAtual) == PREMIUM)
                        {
                            podeImprimir = 0;
                        }
                        if (tipoUsuario == INFANTIL && getRestricaoIdade(conteudoAtual) == ADULTO)
                        {
                            podeImprimir = 0;
                        }

                        if (podeImprimir)
                        {
                            if (strstr(getTituloConteudo(conteudoAtual), termoBusca) != NULL ||
                                strcmp(getCodConteudo(conteudoAtual), termoBusca) == 0)
                            {

                                contadorImpressao++;
                                printf("%d-", contadorImpressao);
                                printaConteudo(conteudoAtual);
                            }
                        }
                    }

                    if (contadorImpressao == 0)
                    {
                        printf("NENHUM CONTEUDO ENCONTRADO!\n");
                    }
                }
            }
        }
        else if (strcmp(comando, "COS") == 0 || strcmp(comando, "COSP") == 0)
        {
            char *cpfUsuario = strtok(args, " ");
            char *termoBusca = strtok(NULL, "");

            tUsuario *usuarioAlvo = NULL;
            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            if (usuarioAlvo == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
            else
            {
                TipoAssinatura assinaturaUsuario = getAssinaturaUsuario(usuarioAlvo);
                TipoUsuario tipoUsuario = getTipoUsuario(usuarioAlvo);

                if (strcmp(comando, "COSP") == 0 && assinaturaUsuario == PADRAO)
                {
                    printf("A CONTA DE CPF %s NAO POSSUI PERMISSAO PARA EXECUTAR ESSE COMANDO!\n", cpfUsuario);
                }
                else
                {
                    printf("# - TIPO ID; NOME; DURACAO; DISP. IDIOMA; ANO; PRODUTORA\n");
                    int contadorImpressao = 0;

                    for (int i = 0; i < qtdConteudos; i++)
                    {
                        tConteudo *conteudoAtual = conteudos[i];
                        if (getTipoConteudo(conteudoAtual) != 'S')
                        {
                            continue;
                        }

                        int podeImprimir = 1;
                        if (strcmp(comando, "COS") == 0 && getRestricaoConteudo(conteudoAtual) == PREMIUM)
                        {
                            podeImprimir = 0;
                        }
                        if (tipoUsuario == INFANTIL && getRestricaoIdade(conteudoAtual) == ADULTO)
                        {
                            podeImprimir = 0;
                        }

                        if (podeImprimir)
                        {
                            if (strstr(getTituloConteudo(conteudoAtual), termoBusca) != NULL ||
                                strcmp(getCodConteudo(conteudoAtual), termoBusca) == 0)
                            {

                                contadorImpressao++;
                                printf("%d-", contadorImpressao);
                                printaConteudo(conteudoAtual);
                            }
                        }
                    }

                    if (contadorImpressao == 0)
                    {
                        printf("NENHUM CONTEUDO ENCONTRADO!\n");
                    }
                }
            }
        }
        else if (strcmp(comando, "COJ") == 0 || strcmp(comando, "COJP") == 0)
        {
            char *cpfUsuario = strtok(args, " ");
            char *termoBusca = strtok(NULL, "");

            tUsuario *usuarioAlvo = NULL;
            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            if (usuarioAlvo == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
            else
            {
                TipoAssinatura assinaturaUsuario = getAssinaturaUsuario(usuarioAlvo);
                TipoUsuario tipoUsuario = getTipoUsuario(usuarioAlvo);

                if (strcmp(comando, "COJP") == 0 && assinaturaUsuario == PADRAO)
                {
                    printf("A CONTA DE CPF %s NAO POSSUI PERMISSAO PARA EXECUTAR ESSE COMANDO!\n", cpfUsuario);
                }
                else
                {
                    printf("# - TIPO ID; NOME; DURACAO; DISP. IDIOMA; ANO; PRODUTORA\n");
                    int contadorImpressao = 0;

                    for (int i = 0; i < qtdConteudos; i++)
                    {
                        tConteudo *conteudoAtual = conteudos[i];
                        if (getTipoConteudo(conteudoAtual) != 'J')
                        {
                            continue;
                        }

                        int podeImprimir = 1;
                        if (strcmp(comando, "COJ") == 0 && getRestricaoConteudo(conteudoAtual) == PREMIUM)
                        {
                            podeImprimir = 0;
                        }
                        if (tipoUsuario == INFANTIL && getRestricaoIdade(conteudoAtual) == ADULTO)
                        {
                            podeImprimir = 0;
                        }

                        if (podeImprimir)
                        {
                            if (strstr(getTituloConteudo(conteudoAtual), termoBusca) != NULL ||
                                strcmp(getCodConteudo(conteudoAtual), termoBusca) == 0)
                            {

                                contadorImpressao++;
                                printf("%d-", contadorImpressao);
                                printaConteudo(conteudoAtual);
                            }
                        }
                    }

                    if (contadorImpressao == 0)
                    {
                        printf("NENHUM CONTEUDO ENCONTRADO!\n");
                    }
                }
            }
        }
        else if (strcmp(comando, "GRAC") == 0)
        {
            char *cpfUsuario = strtok(args, " ");
            char *idConteudo = strtok(NULL, "");

            tUsuario *usuarioAlvo = NULL;
            for (int i = 0; i < qtdUsuarios; i++)
            {
                if (strcmp(getCpfUsuario(usuarios[i]), cpfUsuario) == 0)
                {
                    usuarioAlvo = usuarios[i];
                    break;
                }
            }

            tConteudo *conteudoAlvo = NULL;
            if (usuarioAlvo != NULL)
            {
                for (int i = 0; i < qtdConteudos; i++)
                {
                    if (strcmp(getCodConteudo(conteudos[i]), idConteudo) == 0)
                    {
                        conteudoAlvo = conteudos[i];
                        break;
                    }
                }
            }

            if (usuarioAlvo == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
            }
            else if (conteudoAlvo == NULL)
            {
                printf("NENHUM CONTEUDO ENCONTRADO!\n");
            }
            else if (getAssinaturaUsuario(usuarioAlvo) == PADRAO && getRestricaoConteudo(conteudoAlvo) == PREMIUM)
            {
                printf("USUARIO DE CPF %s NAO TEM ACESSO AO CONTEUDO %s! OPERACAO NAO PERMITIDA\n", cpfUsuario, idConteudo);
            }
            else
            {
                printf("LISTA DE AVALIACOES DO CONTEUDO %s %s - NOTA MEDIA: %.1f\n",
                       getCodConteudo(conteudoAlvo), getTituloConteudo(conteudoAlvo), getNotaMediaConteudo(conteudoAlvo));

                int qtdAvaliacoes = getQtdAvaliacoes(conteudoAlvo);
                for (int i = 0; i < qtdAvaliacoes; i++)
                {
                    tAvaliacao *avaliacaoAtual = getAvaliacaoPosicao(conteudoAlvo, i);
                    char *cpfAvaliador = getCpfAvaliacao(avaliacaoAtual);
                    char *nomeAvaliador = NULL;

                    for (int j = 0; j < qtdUsuarios; j++)
                    {
                        if (strcmp(getCpfUsuario(usuarios[j]), cpfAvaliador) == 0)
                        {
                            nomeAvaliador = getNomeUsuario(usuarios[j]);
                            break;
                        }
                    }

                    if (nomeAvaliador != NULL)
                    {
                        printf("%d- %s -%d\n", i + 1, nomeAvaliador, getNotaAvaliacao(avaliacaoAtual));
                    }
                }
            }
        }
        else
        {
            printf("Comando desconhecido: %s\n", comando);
        }
    }

    // --- Bloco de Libertação de Memória ---
    for (int i = 0; i < qtdUsuarios; i++) liberaUsuario(usuarios[i]);
    if (usuarios != NULL) free(usuarios);

    for (int i = 0; i < qtdDistribuidores; i++) liberaDistribuidor(distribuidores[i]);
    if (distribuidores != NULL) free(distribuidores);

    for (int i = 0; i < qtdConteudos; i++) liberaConteudo(conteudos[i]);
    if (conteudos != NULL) free(conteudos);

    return 0;
}