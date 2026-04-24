<h1 align="center">🏥 HealthCareProject</h1>
<p align="center">
  Sistema de gestão de clínica médica desenvolvido em C
</p>
<p align="center">
  <img src="https://img.shields.io/badge/linguagem-C-00599C?style=for-the-badge&logo=c&logoColor=white"/>
  <img src="https://img.shields.io/badge/plataforma-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white"/>
  <img src="https://img.shields.io/badge/estado-Concluído-brightgreen?style=for-the-badge"/>
</p>

---

## 📋 Sobre o Projeto

O **HealthCareProject** é uma aplicação de consola que simula o sistema de gestão de uma clínica médica. Permite gerir médicos e utentes, com uma fila de espera por médico, tudo persistido em ficheiros de dados.

## ✨ Funcionalidades

- **Gestão de Médicos** — registar, listar e remover médicos
- **Gestão de Utentes** — registar, listar e remover utentes (pacientes)
- **Fila de Espera** — adicionar/remover utentes da fila de um médico e chamar o próximo
- **Relatórios** — visualizar o médico com mais doentes
- **Persistência de Dados** — todos os dados são guardados automaticamente em ficheiros

## 🛠️ Tecnologias

| Tecnologia | Descrição |
|---|---|
| C | Linguagem principal |
| Listas Ligadas | Estrutura de dados para médicos e utentes |
| Ficheiros (I/O) | Persistência de dados |
| Visual Studio Code | IDE de desenvolvimento |

## 📂 Estrutura do Projeto

```
HealthCareProject/
├── main.c              # Ponto de entrada e carregamento de dados
├── funcoes.c           # Lógica de negócio (CRUD, filas, persistência)
├── menus.c             # Interface de menus ASCII
├── headers/
│   ├── funcoes.h
│   └── menus.h
└── data/               # Ficheiros de dados persistidos
```

## 🚀 Como Executar

**Pré-requisitos:** GCC ou Visual Studio Code com extensão C/C++

```bash
# Compilar
gcc main.c funcoes.c menus.c -o healthcare

# Executar
./healthcare
```

Ou abre o projeto no VS Code e usa o botão **Run**.

## 📌 Notas

- Interface inteiramente em Português
- Inserção ordenada por código
- Dados guardados após cada modificação
