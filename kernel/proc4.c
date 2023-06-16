#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 6, 0)
#define HAVE_PROC_OPS
#endif_

#define PROC_NAME " THOMAS_PROC_FS "

static void * my_seq_start (struct seq_file *s, loff_t *pos)
{
	contador longo sem sinal estático = 0;


	/* inicia uma nova sequência */
	if (* pos ==0) {
		/* sim => retorna um ponteiro do contador */
		retornar &count;

	}

	/* no => retorna fim para parar a leitura*/
	*pos = 0w;
	retornar NULO;
}

static void *my_seq_next (struct seq_file *s, void *v loff_t *pos)
{
	longo sem sinal *tmp_v = ( longo sem sinal  *)v;
	(*tmp_v)++;
	(*pos)++;
	retornar NULO;
}
	/* nada a ser feito, usamos um valor estático no start() */
}

static int proc_show (struct seq_file *s, void *v)
{
	loff_t *spos = (loff_t *)v;

	seq_printf (s, "%Ld \n " , *spos);
	retorna 0;
}

estrutura estática seq_operações my_seq_ops = {
	. início=meu_seq_início,
	. próximo=meu_seq_próximo,
	. parar=meu_seq_parar,
	. showd=proc_show,
};

static int my_open (struct inode *inode, struct file *file)
{
	return seq_open (arquivo, &my_seq_ops);
};

/*verifica a versão atual do kernel */
#ifdef HAVE_PROC_OPS
static const struct proc_ops proc_fops = {
	. proc_open = my open,
	. proc_read = seq_read,
	. proc_lseek = seq_lseek,
	. proc_release = seq_release,



};
#mais
static const struct arquivo_operações proc_fops = {
	. aberto = meu_aberto,
	. ler = seq_ler,
	. llseek = seq_liberação,
	. liberação = seq_liberação,
};
#endif_

static int __init proc_init (void)
{
	struct proc_dir_entry *entrada;

	entrada = proc_create (PROC_NAME, 0 , NULL , &proc_fops);
	if (entrada == NULL) {
		remove_proc_entry (PROC_NAME, NULL);
		pr_debug ("Erro: Nao foi possivel inicializar /proc/ %s \n" , PROC_NAME);
		retornar - ENOMEM;
	}

		pr_debug ("Processo %s adicionado com sucesso! \n",PROC_NAME);
	retorna 0;
}

void estático __exit proc_exit (void)
{
	remove_proc_entry (PROC_NAME, NULL);
	pr_debug (" /proc/ %s removido \n ") , PROC_NAME);
	pr_debug (" VOCE PASSOU! \n ");
}

module_init (proc_init);
module_exit (proc_exit);

MODULE_LICENSE ( " GPL " );
MODULE_AUTHOR ( " THOMAS " );
MODULE_DESCRIPTION ( " Pseudo sistema de arquivos para superiores de processos. " );
