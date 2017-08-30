%------------------------------------------------------------------------------

% EM USO NORMAL, ESTE ARQUIVO NÃO DEVE SER MODIFICADO!

% Esta classe "tese" define o padrão para dissertações, teses e documentos
% correlatos produzidos no Programa de Pós-Graduação em Informática da
% Universidade Federal do Paraná, em Curitiba PR.
%
% Esta classe segue o modelo da classe "book" e aceita todas as suas opções.
% Ela também define as seguintes opções específicas:
% 
%    defesa: versão prévia (só frente, espaçamento 1.5,)
%    final:  versão final (frente/verso, espaçamento 1, páginas complementares)

% Os seguintes ambientes e comandos também são definidos:
%
% \descr{...}		: descrição do documento na folha de rosto
% \instit{short}{long}	: instituição (abreviado e por extenso)
% \advisor{Nome}	: define o orientador
% \coadvisor{Nome}	: define o co-orientador, se houver
% \field{Área}		: define a área de concentração da pesquisa
% \local{Cidade}	: define o local da defesa
% \keywords{}{}...	: define três palavras-chave e três keywords
% \begin{resumo}	: define a página de resumo
% \begin{abstract}	: define a página de abstract
% \begin{agradece}	: define a página de agradecimentos
% \begin{dedica}	: define a página de dedicatória
% \begin{ficha}		: define a ficha catalográfica
% \begin{aprovacao}	: define a folha de aprovação
%
% Software fornecido sob a licença GNU GPL. Pode ser usada e modificada
% livremente, desde que mantidas as informações deste cabeçalho.

%------------------------------------------------------------------------------

% definição da classe e versão
\ProvidesClass{ppginf}[2016/10/19 Manuscript class for PPGInf/UFPR]
\def\@classversion{0.9.5}

%------------------------------------------------------------------------------

% opções desta classe

% define flag de versão final do documento
\newif\iffinalmode

% defesa: só frente, espaçamento 1,5 e menos páginas iniciais
\DeclareOption{defesa}{\finalmodefalse}

% aprovada: frente/verso, espaçamento 1 e mais páginas iniciais
\DeclareOption{final}{\finalmodetrue}

% demais opções devem ser encaminhadas à classe de base (book)
\DeclareOption*{\PassOptionsToClass{\CurrentOption}{book}}

% processa as opcoes definidas acima
\ProcessOptions

%------------------------------------------------------------------------------

%% Carregar a classe de base
\iffinalmode
  \if@twoside
    \LoadClass[12pt,a4paper,twoside]{book}	% twoside na final
  \else%
    \LoadClass[12pt,a4paper,oneside]{book}	% oneside na final
  \fi
\else
  \if@twoside
    \LoadClass[12pt,a4paper,twoside]{book}	% twoside na defesa
  \else%
    \LoadClass[12pt,a4paper,oneside]{book}	% oneside na defesa
  \fi
\fi

%------------------------------------------------------------------------------

%% Ajustes no layout geral do texto

% dimensões da página e margens
\RequirePackage{geometry}
\geometry{a4paper}
\geometry{right=2cm,left=2cm,top=3cm,bottom=2cm}
\geometry{bindingoffset=1cm}

% indentar o primeiro parágrafo (português)
\RequirePackage{indentfirst}

% indentação dos parágrafos é 10mm
\setlength{\parindent}{15mm}

% aumentar o espaço entre a legenda e a tabela
\usepackage{caption} 
\captionsetup[table]{skip=10pt}

% espaçamento entre linhas
\RequirePackage{setspace}

\iffinalmode
  % final: espaçamento 1
  \singlespacing
\else
  % default: espaçamento 1.5
  \onehalfspacing
\fi

% relaxar o espaçamento entre caracteres
\sloppy

% impedir linhas órfãs/viúvas (linhas isoladas no início/fim de uma página)
\clubpenalty=10000
\widowpenalty=10000
\displaywidowpenalty 10000
\raggedbottom

% sumário: adiciona entrada para bibliografia e remove entradas
% de sumário, lista de figuras e lista de tabelas.
\RequirePackage[nottoc,notlot,notlof]{tocbibind}

% melhor formatação de URLs na bibliografia
\RequirePackage[obeyspaces,hyphens]{url}

%------------------------------------------------------------------------------

% formatação de cabeçalho e rodapé
\RequirePackage{fancyhdr}
\setlength{\headheight}{15pt}

% sem linhas separadoras para cabeçalho e rodapé
\renewcommand{\headrulewidth}{0pt}
\renewcommand{\footrulewidth}{0pt}

% define o estilo de página do preâmbulo (páginas iniciais) do documento
\fancypagestyle{frontmatter}{
  \fancyhf{}
}

% define o estilo de página do corpo do documento (capítulos)
\fancypagestyle{mainmatter}{
  \fancyhf{}
  \if@twoside
    \fancyhead[LE,RO]{\thepage}
  \else
    \fancyhead[R]{\thepage}
  \fi
}

% define o estilo default "plain" como nulo nas páginas iniciais (frontmatter)
% e igual a mainmatter no corpo do documento (para por números de página na
% primeira página de cada capítulo).
\fancypagestyle{plain}{
  \fancyhf{}
  \if@mainmatter
    \if@twoside
      \fancyhead[LE,RO]{\thepage}
    \else
      \fancyhead[R]{\thepage}
    \fi
  \fi
}

%------------------------------------------------------------------------------

% pacotes para gerar um arquivo PDF "rico" (bookmarks, links, metadados)
\RequirePackage[plainpages,pdfpagelabels]{hyperref}	% PDF com links, metadados
\RequirePackage{bookmark}				% cria um índice no PDF

% ajustar metadados e propriedades do PDF gerado
\hypersetup{
  % pdftitle, author, etc definidos mais abaixo
%  bookmarks   = true,
%  pageanchor  = false,
  hypertexnames = false,
%  bookmarkstype = page,
  pdfview     = Fit,
  pdfborder   = {0 0 0},
  colorlinks  = false,
  linkcolor   = blue,
  anchorcolor = blue,
  citecolor   = blue,
  filecolor   = blue,
%  pagecolor   = blue,
  urlcolor    = blue
}

\RequirePackage{microtype}	% melhorar a qualidade da tipografia no PDF

%------------------------------------------------------------------------------

% definição de autor, orientador, local, área, palavras-chave, etc

% valores default (não mudá-los, pois poderão ser testados em macros)
\def\@advisor{}			% orientador
\def\@coadvisor{}		% co-orientador
\def\@field{}			% área de concentração
\def\@local{}			% local
\def\@descr{}			% descrição do documento
\def\@instshort{undef}		% instituição (abreviação)
\def\@instlong{undef}		% instituição (por extenso)
\def\@pcs{}			% palavras-chave
\def\@kws{}			% keywords

% instituição
\newcommand{\instit}[2]{
  \def\@instshort{#1}
  \def\@instlong{#2}
}

% descrição do documento na folha de rosto
\newcommand{\descr}[1]{\def\@descr{#1}}

% orientadores
\newcommand{\advisor}[1]{\def\@advisor{#1}}
\newcommand{\coadvisor}[1]{\def\@coadvisor{#1}}

% área/tema do texto
\newcommand{\field}[1]{\def\@field{#1}}

% local (cidade)
\newcommand{\local}[1]{\def\@local{#1}}

% palavras-chave em português e inglês
\newcommand{\pchave}[1]{\def\@pcs{#1}}
\newcommand{\keyword}[1]{\def\@kws{#1}}

%------------------------------------------------------------------------------

% ambientes da parte inicial do documento

% resumo
\newenvironment{resumo}
{
  \clearpage
%  \phantomsection
%  \addcontentsline{toc}{chapter}{Resumo}
  \begin{center}
  {\huge\textbf{Resumo}}
  \end{center}
  \vspace{0.5ex}
}{
  % somente mostrar palavras-chave se estiverem definidas
  \ifx\@pcs\@empty
  \else
    \vspace{4ex}
    \noindent\textbf{Palavras-chave:} {\@pcs}.
  \fi
  \vfill
  \cleardoublepage
}

% abstract
\newenvironment{abstract}
{
  \clearpage
%  \phantomsection
%  \addcontentsline{toc}{chapter}{Abstract}
  \begin{center}
  {\huge\textbf{Abstract}}
  \end{center}
  \vspace{0.5ex}
}{
  % somente mostrar keywords se estiverem definidas
  \ifx\@kws\@empty
  \else
    \vspace{4ex}
    \noindent\textbf{Keywords:} {\@kws}.
  \fi
  \vfill
  \cleardoublepage
}

% agradecimentos e dedicatória (só na versão aprovada)
\iffinalmode
  % ambiente da ficha catalográfica
  \newenvironment{ficha}{}{\cleardoublepage}

  % ambiente da folha de aprovação
  \newenvironment{aprovacao}{}{\cleardoublepage}

  % ambiente de agradecimentos
  \newenvironment{agradece}
  {
    \begin{center}
    {\huge\textbf{Agradecimentos}}
    \end{center}
    \vspace{0.5ex}
  }{
    \vfill
    \cleardoublepage
  }

  % ambiente de dedicatória
  \newenvironment{dedica}
  {
    \vspace*{\fill}
    \hfill
    \begin{minipage}[t]{6cm}
    \em
  }{
    \end{minipage}
    \cleardoublepage
  }
\else
  % Na versão de defesa, esses ambientes não geram nada
  \newenvironment{ficha}{\comment}{\endcomment}
  \newenvironment{agradece}{\comment}{\endcomment}
  \newenvironment{dedica}{\comment}{\endcomment}
  \newenvironment{aprovacao}{\comment}{\endcomment}
\fi

% lista de acrônimos (siglas e abreviações)
\newenvironment{listaacron}
{
  \chapter*{Lista de Acr\^onimos}
%  \phantomsection
%  \addcontentsline{toc}{chapter}{Lista de Acr\^onimos}
}{
  \vfill
  \cleardoublepage
}

% lista de símbolos
\newenvironment{listasimb}
{
  \chapter*{Lista de S\'{\i}mbolos}
%  \phantomsection
%  \addcontentsline{toc}{chapter}{Lista de S\'{\i}mbolos}
}{
  \vfill
  \cleardoublepage
}

%------------------------------------------------------------------------------

% construção das páginas iniciais
\renewcommand{\titlepage}
{
  % páginas iniciais não são numeradas
  %\pagestyle{empty}
  %\thispagestyle{empty}

  % ajustar tags do PDF final
  \hypersetup{
    pdftitle    = {\@title},
    pdfauthor   = {\@author},
    pdfsubject  = {\@field},
    pdfproducer = {\@instshort\ - \@instlong},
    pdfcreator  = {LaTeX, using PPGInf class V. \@classversion},
    pdfkeywords = {\@pcs, \@kws}
  }

  % primeira capa (só na versão aprovada)
  \iffinalmode
%    \phantomsection
%    \thispagestyle{empty}
    \begin{center}
      \begin{doublespace}
        \textsc{\Large\@instlong}
        \\
        \vspace{3cm}
        \textsc{\Large\@author}
        \\
        \vfill
        \DeclareRobustCommand\\{\linebreak}
        \textsc{\Large\@title}
        \vfill
        \textsc{\Large\@local\\\@date}
      \end{doublespace}
    \end{center}
    \cleardoublepage
  \fi

  % folha de rosto
  \clearpage
%  \phantomsection
%  \addcontentsline{toc}{chapter}{Rosto}
%  \thispagestyle{empty}

  % autor
  \begin{center}
    \textsc{\Large\@author}
  \end{center}

  \vfill\vfill

  % título
  \begin{doublespace}
    \begin{center}
      \DeclareRobustCommand\\{\linebreak }
      \textsc{\Large\@title}
    \end{center}
  \end{doublespace}

  \vspace{1cm}

  % selo descritivo
  \hfill
  \begin{minipage}{9cm}

    % descrição
    \ifx\@descr\@empty
    \else
      \@descr.
    \fi

    % área de concentração
    \ifx\@field\@empty
    \else
      \vspace{1em}
      \'Area de concentra\c{c}\~ao: \emph{\@field}.
    \fi

    % orientador
    \ifx\@advisor\@empty
    \else
      \vspace{1em}
      Orientador: \@advisor.
    \fi

    % coorientador
    \ifx\@coadvisor\@empty
    \else
      \vspace{1em}
      Co-orientador: \@coadvisor.
    \fi

  \end{minipage}

  \vfill

  % local e data
  \begin{center}
    \begin{doublespace}
      \textsc{\Large\@local\\\@date}
    \end{doublespace}
  \end{center}

  % that's all, folks!
  \cleardoublepage
}

%------------------------------------------------------------------------------
