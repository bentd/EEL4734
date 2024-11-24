# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|

  config.vm.box = "ubuntu/focal64"

  config.vm.provider "virtualbox" do |vb|
    vb.memory = "8192"
    vb.name = "Lab"
    vb.cpus = 3
    # Enable USB support and specify the controller type
    vb.customize ["modifyvm", :id, "--usb", "on"]
    vb.customize ["modifyvm", :id, "--usbxhci", "on"] # use "--usbehci" for USB 2.0, or use "--usbxhci" for USB 3.0
    # Set the graphics controller
    vb.customize ["modifyvm", :id, "--graphicscontroller", "VMSVGA"]
    # Optionally, set other display settings like VRAM size
    vb.customize ["modifyvm", :id, "--vram", "128"] # Set VRAM to 128MB
  end

  # Enable USB filters
  config.trigger.before :up do
    $script = <<-SCRIPT
    echo "Setting up USB filters"
    VM_NAME="Lab"

    # Check and add filter for BeagleBone Black
    FILTER_EXISTS=$(VBoxManage showvminfo "$VM_NAME" --machinereadable | grep "USBFilterName[0-9]*=.*BeagleBone Black")
    if [ -z "$FILTER_EXISTS" ]; then
      VBoxManage usbfilter add 0 --target "$VM_NAME" --name "BeagleBone Black" --vendorid 0x1D6B --productid 0x0104 --remote no
      echo "Added USB filter for BeagleBone Black"
    else
      echo "USB filter for BeagleBone Black already exists. Skipping."
    fi

    # Check and add filter for Prolific USB-Serial Controller
    FILTER_EXISTS=$(VBoxManage showvminfo "$VM_NAME" --machinereadable | grep "USBFilterName[0-9]*=.*Prolific USB-Serial Controller")
    if [ -z "$FILTER_EXISTS" ]; then
      VBoxManage usbfilter add 1 --target "$VM_NAME" --name "Prolific USB-Serial Controller" --vendorid 0x067B --productid 0x23A3 --remote no
      echo "Added USB filter for Prolific USB-Serial Controller"
    else
      echo "USB filter for Prolific USB-Serial Controller already exists. Skipping."
    fi

    # Check and add filter for Realtek USB3.0 Card Reader
    FILTER_EXISTS=$(VBoxManage showvminfo "$VM_NAME" --machinereadable | grep "USBFilterName[0-9]*=.*Realtek USB3.0 Card Reader")
    if [ -z "$FILTER_EXISTS" ]; then
      VBoxManage usbfilter add 2 --target "$VM_NAME" --name "Realtek USB3.0 Card Reader" --vendorid 0x0BDA --productid 0x0306 --remote no
      echo "Added USB filter for Realtek USB3.0 Card Reader"
    else
      echo "USB filter for Realtek USB3.0 Card Reader already exists. Skipping."
    fi
    SCRIPT

    # Execute the shell script
    system($script)
  end  
end
