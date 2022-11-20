fn main() {
  let _end_direto_de_bloco = 8;
  let bloco_de_disco = 1024;
  let entrada_de_dir = 4;

  let arquivos_armazenados = (bloco_de_disco as f64) / (entrada_de_dir as f64);
  println!("Número de arquivos armazenados em cada endereço de bloco do disco = {}", arquivos_armazenados);

  let blocos: [f64; 3] = [1100.0, 800.0, 300.0];
  let mut total:f64 = 0.0;

  for bloco in blocos {
    let result = bloco / arquivos_armazenados + 1.0;
    total += result.ceil();
    println!("Blocos utilizados: {}...", result.ceil());
  }

  println!("Total de blocos: {}", total);
}
