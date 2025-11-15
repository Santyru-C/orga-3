#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>

char* nombre = "nulo";

static ssize_t nulo_read(struct file *filp, char __user *data, size_t s, loff_t *off) {
  return 0;
}

static ssize_t nulo_write(struct file *filp, const char __user *data, size_t s, loff_t *off) {
  return 0;
}

static struct file_operations nulo_operaciones = {
  .owner = THIS_MODULE,
  // Entendemos que aca tenemos que poner las estructuras para cada operacion que permita el dispositivo
  .read = nulo_read,
  .write = nulo_write
};

static struct cdev nulo_device;
static dev_t major;
static struct class *nulo_class;

static int __init hello_init(void) {
  
  // Aca deberíamos inicializar el dispositivo con cdev_init
	cdev_init(&nulo_device , &nulo_operaciones);
  
  // major nos lo define la función, 0 es el minor y 1 el name
  alloc_chrdev_region(&major, 0, 1, nombre);
  cdev_add(&nulo_device, major, 1);

  // Definimos esto para que sepa montarse solito
  nulo_class = class_create(THIS_MODULE, nombre);
  device_create(nulo_class, NULL, major, NULL, nombre);

  printk(KERN_ALERT "Se inicio NULO\n");
  return 0;
}

static void __exit hello_exit(void) {
  
  // Aca hay que borrar toda la basura que armamos

  unregister_chrdev_region(major, 1);
  cdev_del(&nulo_device);

  device_destroy(nulo_class, major);
  class_destroy(nulo_class);

  printk(KERN_ALERT "Se descargo NULO\n");

}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Not Mates y Bizcochos");
MODULE_DESCRIPTION("Una suerte de '/dev/null'");
