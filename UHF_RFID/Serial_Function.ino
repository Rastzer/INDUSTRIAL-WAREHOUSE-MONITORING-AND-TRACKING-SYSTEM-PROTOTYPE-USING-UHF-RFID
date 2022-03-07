void serialevent1() {
  if (Serial1.available()) {
    read_rfid = Serial1.read();
    data_read += String(read_rfid, HEX);
    if (read_rfid == 0x7E) {
      parsing = true;
    }
    pharse();
  }
}
