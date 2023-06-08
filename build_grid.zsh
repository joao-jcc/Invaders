#!/usr/local/bin/zsh

# uso: zsh build_grid.zsh root_folder number_images grid_format(num1xnum2) output_file(without extension) 

# Caminho para a pasta com as imagens
root_folder=$1
# Número de imagens no grid
num_images=$2
# Formato do grid
grid_shape=$3
# Nome do arquivo gerado, sem extensão
output_file=$4

# Array com os caminhos das imagens
images=()
for ((i=1; i<($num_images+1); i++))
do
  images+=("$root_folder/$i.png")
done

# Comando base para ontar o grid
command="montage -tile $grid_shape -geometry +0+0 -background none"

# Iterar pelas imagens e adicionar ao comando base
for ((i=0; i<$num_images; i++))
do
  command+="$(printf '%s ' "${images[$i]}")"
done

# Adicionar o nome do arquivo de saída no comando
command+=$output_file

# Executar o comando
eval "$command"
