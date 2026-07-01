# 🪐 Custom x86 Kernel & Snake Game in C++ (No Standard Libraries)

Este é um projeto de desenvolvimento de baixo nível (**OSDev**) onde construí um mini Sistema Operacional x86 do zero. O projeto inclui um estágio de boot, um kernel com shell interativo (comandos como `HELP`, `CLEAR`, `MKDIR`) e um jogo da **Cobrinha (Snake)** escrito em **C++ Puro focado em Programação Orientada a Objetos (POO)**, rodando diretamente no metal da máquina virtual, sem nenhuma dependência ou biblioteca padrão (`glibc`).

---

## 👾 DETALHE!
* A MAIORIA DAS COISAS ESTÃO NA BRANCH FEATURE/SHELL OU NA DEV!!
* MEU CONTATO DO DISCORD: ahmia_2
* Código: Fernando & Áquila
* Tester: Áquila

  
---

## 🚀 Funcionalidades Atuais

* **Bootloader Customizado:** Código Assembly de 32 bits (`boot.asm`) que inicializa o processador.
* **Kernel Shell:** Terminal interativo com buffer de comandos feito em C.
* **Motor Gráfico na Força Bruta:** Escrita direta na memória de vídeo VGA (`0xB8000`) para renderizar caracteres e cores.
* **Snake Game em C++:** Jogo completo estruturado com classes (`Snake` e `Food`), incluindo:
  * Movimentação com física de arrasto do corpo.
  * Sistema de leitura não-bloqueante do teclado (Porta `0x60`).
  * Lógica de colisão em si mesma com Reset automático do estado.
  * Geração pseudo-aleatória de comida via matemática pura de congruência linear.

---

## 🛠️ Tecnologias Utilizadas

* **Assembly NASM** (Modo Protegido x86 de 32 bits)
* **C puro** (Estrutura interna do Kernel e Shell)
* **C++** (Orientação a Objetos para o jogo Snake)
* **GNU Make** (Automação da compilação e linkagem)
* **QEMU** (Emulador de Hardware/Processador)

---

## 📦 Como Compilar e Executar

Como este projeto compila um código de 32 bits em ambiente livre (`-ffreestanding`), precisamos garantir que as dependências necessárias de arquitetura cruzada estejam instaladas no seu sistema Linux host.

### 1. Pré-requisitos (No Linux Host)

Antes de rodar, instale o compilador, as ferramentas de 32 bits (`multilib`) e o emulador QEMU:

```bash
# Ubuntu / Debian / Pop!_OS / Mint
sudo apt update
sudo apt install gcc gcc-multilib g++-multilib nasm qemu-system-i386 make

# Arch Linux / Manjaro
sudo pacman -S gcc-multilib nasm qemu-desktop make

# Fedora / RHEL
sudo dnf install glibc-devel.i686 libstdc++-devel.i686 nasm qemu-system-x86 make
