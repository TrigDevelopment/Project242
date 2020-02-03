void breedTest() {
  auto to = Program{ *,sin,sin,sin,*,sin,x,1,x };
  auto from = Program{ sin,+,*,1,1,1 };
  breed(to, from, 2, 0) == ?
}