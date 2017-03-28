void Atuar(String state) {
  valor_luminosidade = state.toInt();
  Serial.println("\n\n[STRING]\t" + state + "\n\n");
  Serial.println(valor_luminosidade);
  Serial.println("[light] " + state);

  if (valor_luminosidade == 0) {
    analogWrite(luz, valor_luminosidade);
    Serial.println("\n[apagada]");
  }
  else if (valor_luminosidade > 0 && valor_luminosidade < 256) {
    analogWrite(luz, valor_luminosidade);
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

void Estado(String state){
}

void Valor(String state){
  JsonObject& root = jsonBuffer.createObject();
  root["serial"] = uuid_dispositivo;  //  root["time"] = 1351824120;   //  JsonArray& data = root.createNestedArray("data");  //  data.add(double_with_n_digits(48.756080, 6));  //  data.add(double_with_n_digits(2.302038, 6));
  root.printTo(JSON);

  socket.emit("/post/dispositivo/", JSON);
}

