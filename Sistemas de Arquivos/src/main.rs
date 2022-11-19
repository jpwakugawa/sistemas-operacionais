fn main() {
  let _end_direto_de_bloco = 8;
  let bloco_de_disco = 1024;
  let entrada_de_dir = 4;

  let arquivos_armazenados = (bloco_de_disco as f64) / (entrada_de_dir as f64);
  println!("Número de arquivos armazenados em cada endereço de bloco do disco = {}", arquivos_armazenados);

  let blocos = (1100 as f64) / arquivos_armazenados;
  println!("Número de blocos utilizados no /: {}", blocos.ceil());
  
  let blocos = (800 as f64) / arquivos_armazenados;
  println!("Número de blocos utilizados no /home: {}", blocos.ceil());
  
  let blocos = (300 as f64) / arquivos_armazenados;
  println!("Número de blocos utilizados no /home/hillsong: {}", blocos.ceil());
}
