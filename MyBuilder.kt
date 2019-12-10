import java.io.*

//kotlinc MyBuilder.kt -include-runtime -d MyBuilder.jar
//java -jar MyBuilder.jar

lateinit var path: String

fun main(args: Array<String>) {
    path = args[0]
    File("$path\\a.exe").delete()
    runCommand("gcc -masm=intel -nostdlib $path\\main.c -o $path\\a.exe")
    runCommand("objcopy $path\\a.exe -O binary")
    runCommand("nasm -f bin $path\\boot.asm -o $path\\boot.bin")
    createDisk()
    runCommand("qemu-system-i386 $path\\disk.img")
}

fun runCommand(command: String) {
    Runtime.getRuntime().exec(command).apply {
        waitFor()
        destroy()
    }
}

fun createDisk() {
    val bootFile = FileInputStream("$path\\boot.bin")
    val mainFile = FileInputStream("$path\\a.exe")
    val fontFile = FileInputStream("$path\\myfont.bin")
    val imageFile = FileInputStream("$path\\image.bmp")

    val bootBytes = ByteArray(510)
    bootFile.read(bootBytes, 0, bootBytes.size)

    val mainBytes = ByteArray(7168)
    mainFile.read(mainBytes, 0, mainBytes.size)

    val fontBytes = ByteArray(8704)
	fontFile.read(fontBytes, 0, fontBytes.size)

    val imageBytes = ByteArray(imageFile.available())
    imageFile.read(imageBytes, 0, imageBytes.size)

    val diskFile = FileOutputStream("$path\\disk.img")

    diskFile.apply {
        write(bootBytes)
        write(byteArrayOf(0x55.toByte(), 0xaa.toByte()))
        write(mainBytes)
        write(fontBytes)
        write(imageBytes)
        close()
    }

}
