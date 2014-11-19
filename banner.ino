  case estado_inicial:           //Estado estacionario; aguarda a entrada de uma das senhas
    Cofre.acende_led(LED_R);     //O LED vermelho fica aceso durante o tempo em que o cofre fica trancado
    chave_ativada = Cofre.leia_chave();			//Funcao criada na biblioteca customizada, a fim de ler se alguma chave foi ativada;
   												                  //caso contrario, retorna 0 (vide arquivo da biblioteca)
    cont = -1;		//Inicia-se cont com -1	

    if(senha[0] != senha_m[0]) cont = 0;      //Armazenamento do estado em que a senha comecou a diferir da senha mestra
    Serial.print("cont = ");
    Serial.println(cont);

    Serial.print("Chave ativada = ");
    Serial.println(chave_ativada);
    if((chave_ativada == senha[0]) && (cont == 0)){     //Recebeu a senha do usuario, verifica se a senha comeca a diferir agora
      Cofre.acende_led(LED_B);                          //Acender o LED azul sempre significa que um caractere foi inserido
      currentState = a1;                                //Direcionamento para o proximo estado de senha do usuario
      Serial.print("currentState: a1");
      delay(trans);
      ti = millis();      //Inicia-se um contador de tempo, a fim de testar se (millis() - ti) vai superar 'temp' no proximo estado
    }
    else{
      if(chave_ativada == senha_m[0]){     //Analogamente, o processo ocorre para o caso da senha mestra
        Cofre.acende_led(LED_B);
        currentState = m1;                 //Proximo estado da senha mestra
        Serial.print("currentState: m1");
        delay(trans);
        ti = millis();
      }
      else{
        if (chave_ativada > 0){		//Se nao e nem o digito da senha do usuario, nem da mestra, encaminhando para 'senha_errada'
          Cofre.acende_led(LED_B);
          Serial.println("Senha errada");
          delay(trans);
          currentState = Cofre.senha_errada(currentState);		//O estado senha errada foi movido para a biblioteca por conveniencia,
        }													              	            //Simplificando o uso e podendo ser usado como um 'estado multiplo'
      }
    }
    break;
