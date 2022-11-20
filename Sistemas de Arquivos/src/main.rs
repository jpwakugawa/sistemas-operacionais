fn main() {
  let _end_direto_de_bloco = 8;
  let tamanho_bloco_disco:f64 = 1024.0;
  let tamanho_entrada_dir:f64 = 4.0;

  let n_arquivos:f64 = tamanho_bloco_disco / tamanho_entrada_dir;
  println!("Cada I-Node terá {} arquivos por bloco de disco", n_arquivos);

  // O número de arquivos alocados em cada diretório
  let diretorios: [f64; 3] = [1100.0, 800.0, 300.0];
  let nomes: [String; 3] = ["/".to_string(), "/home".to_string(), "/home/hillsong".to_string()];
  let mut total:f64 = 0.0;

  for i in 0..3 {
    let result = diretorios[i] / n_arquivos + 1.0;
    total += result.ceil();
    println!("Acessos utilizados no {}: {}...", nomes[i], result.ceil());
  }

  println!("Total de acessos: {}", total);
}
