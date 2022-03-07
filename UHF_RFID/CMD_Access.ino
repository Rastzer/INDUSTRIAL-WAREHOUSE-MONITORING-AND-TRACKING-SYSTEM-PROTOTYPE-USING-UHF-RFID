//mode read single
void Read_Single() {
  Serial1.write(0xBB);
  Serial1.write(0x00);
  Serial1.write(0x22);
  Serial1.write(0x00);
  Serial1.write(0x00);
  Serial1.write(0x22);
  Serial1.write(0x7E);
}

//mode read multi
void Read_Multi() {
  Serial1.write(0xBB);
  Serial1.write(0x00);
  Serial1.write(0x27);
  Serial1.write(0x00);
  Serial1.write(0x03);
  Serial1.write(0x22);
  Serial1.write(0x00);
  Serial1.write(0x20);
  Serial1.write(0x6c);
  Serial1.write(0x7E);
}

//BB 00 28 00 00 28 7E

void Stop_Read_Multi() {
  Serial1.write(0xBB);
  Serial1.write(0x00);
  Serial1.write(0x28);
  Serial1.write(0x00);
  Serial1.write(0x00);
  Serial1.write(0x28);
  Serial1.write(0x7E);
