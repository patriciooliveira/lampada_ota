


void Atuar(String state) {
  int intensidade = state.toInt();
  Serial.println("\n\n[STRING]\t" + state + "\n\n");
  Serial.println(intensidade);
  Serial.println("[light] " + state);

  if (intensidade == 0) {
    analogWrite(luz, intensidade);
    Serial.println("\n[apagada]");
  }
  else if (intensidade > 0 && intensidade < 256) {
    analogWrite(luz, intensidade);
    Serial.println("\n[acesa]");
  }
  else {
    Serial.println("valor invalido");
  }
}

void Debug(String state) {
  Serial.println("\n[ISSO É DO DEBUG]\n");
  Serial.println("\n[" + state + "]\n");
}
void Estado(){}

void Valor(){}
