CREATE TABLE public.association (
	id serial NOT NULL,
	identifiant varchar(20) NOT NULL,
	mot_de_passe varchar(100) NOT NULL,
	view_logout varchar(20) NULL,
	CONSTRAINT association_pkey PRIMARY KEY (id)
);

CREATE TABLE public.transac (
	id serial NOT NULL,
	"date" date NULL,
	reference varchar(20) NULL,
	titre varchar(50) NULL,
	rapproche bool NULL,
	CONSTRAINT "Transaction_pkey" PRIMARY KEY (id)
);

CREATE TABLE public.compte (
	id serial NOT NULL,
	solde float8 NULL,
	solde_dernier_rapprochement float8 NULL,
	date_dernier_rapprochement date NULL,
	"type" varchar(30) NULL,
	nom varchar NULL,
	id_association int4 NULL,
	derniere_modification date NULL,
	id_compte_parent int4 NULL,
	virtuel bool NULL,
	CONSTRAINT compte_pkey PRIMARY KEY (id),
	CONSTRAINT compte_un UNIQUE (id),
	CONSTRAINT compte_id_compteparent_fkey FOREIGN KEY (id_compte_parent) REFERENCES compte(id),
	CONSTRAINT fk_association FOREIGN KEY (id_association) REFERENCES association(id)
);

CREATE TABLE public.operation (
	id serial NOT NULL,
	id_compte int4 NULL,
	id_transaction int4 NULL,
	debit float8 NULL,
	credit float8 NULL,
	CONSTRAINT operation_pkey PRIMARY KEY (id),
	CONSTRAINT operation_id_transaction_fkey FOREIGN KEY (id_transaction) REFERENCES transac(id),
	CONSTRAINT fk_compte FOREIGN KEY (id_compte) REFERENCES compte(id)
);

