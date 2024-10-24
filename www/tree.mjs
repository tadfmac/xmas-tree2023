import pomidi from "./pomidi.mjs";

const COLORS = [
  {data:"red"},     // red
  {data:"lime"},    // green
  {data:"#8080FF"}, // blue
  {data:"fuchsia"}, // purple
  {data:"yellow"},  // yellow
  {data:"aqua"},    // cyan
  {data:"white"}    // white
];

const PATS = [
  [ // 1
    [6],
    [7],
    [10],
    [6,7,10],
    [0,2,4,9,11,14],
    [0,1,2,3,4,5,8,9,11,12,13,14],
    [0,2,4,9,11,14],
    [6,7,10]
  ],
  [ // 2
    [2],
    [1,3,6,7,10],
    [0,4,5,8,9,11,12,13,14],
    [15],
    [2],
    [1,3,6,7,10],
    [0,4,5,8,9,11,12,13,14],
    [15]
  ],
  [ // 3
    [0,1,2,3,4],
    [5,6,7,8],
    [9,10,11],
    [12,13],
    [14,15],
    [12,13],
    [9,10,11],
    [5,6,7,8]
  ],
  [ // 4
    [0,1,2,3,4],
    [0,1,2,3,4,5,6,7,8],
    [0,1,2,3,4,5,6,7,8,9,10,11],
    [0,1,2,3,4,5,6,7,8,9,10,11,12,13],
    [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15],
    [0,1,2,3,4,5,6,7,8,9,10,11,12,13],
    [0,1,2,3,4,5,6,7,8,9,10,11],
    [0,1,2,3,4,5,6,7,8]
  ],
];

const treeSvg = `
<svg class="svgtree" width="900px" height="1200px" viewBox="0 0 900 1200" version="1.1" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
    <title>tree</title>
    <g id="Page-1" stroke="none" stroke-width="1" fill="none" fill-rule="evenodd">
        <g id="tree" transform="translate(17.9592, 18)">
            <polygon id="LEAFS" fill="#004012" points="389.730821 168.813528 479.208289 168.813528 479.208289 271.402405 570.550398 374.235411 522.233912 374.235411 635.871728 501.165627 583.737571 501.165627 710.996099 653.897748 661.635751 653.897748 787.951436 804.85783 738.338541 804.85783 864.220687 954.605685 1.80684546e-14 954.605685 133.454352 804.85783 73.6469692 804.85783 207.526443 653.897748 151.991316 653.897748 279.839121 501.165627 233.433575 501.165627 345.728682 374.235411 301.175149 374.235411 389.730821 271.402405"></polygon>
            <rect id="STEM" fill="#903202" x="365.040788" y="955" width="140" height="208"></rect>
            <circle id="LED-0" fill="#000000" cx="183.040788" cy="856" r="30"></circle>
            <circle id="LED-1" fill="#000000" cx="309.040788" cy="856" r="30"></circle>
            <circle id="LED-2" fill="#000000" cx="435.040788" cy="856" r="30"></circle>
            <circle id="LED-3" fill="#000000" cx="561.040788" cy="856" r="30"></circle>
            <circle id="LED-4" fill="#000000" cx="687.040788" cy="856" r="30"></circle>
            <circle id="LED-5" fill="#000000" cx="624.040788" cy="727" r="30"></circle>
            <circle id="LED-6" fill="#000000" cx="498.040788" cy="727" r="30"></circle>
            <circle id="LED-7" fill="#000000" cx="372.040788" cy="727" r="30"></circle>
            <circle id="LED-8" fill="#000000" cx="246.040788" cy="727" r="30"></circle>
            <circle id="LED-9" fill="#000000" cx="309.040788" cy="602" r="30"></circle>
            <circle id="LED-10" fill="#000000" cx="435.040788" cy="602" r="30"></circle>
            <circle id="LED-11" fill="#000000" cx="561.040788" cy="602" r="30"></circle>
            <circle id="LED-12" fill="#000000" cx="501.040788" cy="477" r="30"></circle>
            <circle id="LED-13" fill="#000000" cx="372.040788" cy="477" r="30"></circle>
            <circle id="LED-14" fill="#000000" cx="435.040788" cy="351" r="30"></circle>
            <polygon id="LED-15" fill="#000000" points="432.540788 219.75 346.430249 265.02099 362.875898 169.135495 293.211009 101.22901 389.485518 87.2395052 432.540788 0 475.596058 87.2395052 571.870568 101.22901 502.205678 169.135495 518.651328 265.02099"></polygon>
        </g>
    </g>
</svg>
`;

class Tree{
  constructor($dom){
    this.midi = null;
    this.deviceNames = [];
    this.devices = {};
    this.wrapper = $dom;
    this.onchange = null;
  }
  async init(){
    console.log("Tree.init()");
    let midi = new pomidi();
    this.midi = await midi.init();
    if(this.midi != null){
      this.midi.setOnChange(this._onChange.bind(this));
      await this._getDeviceList();
    }
    if(this.midi == null){
      return null;
    }else{
      return this;
    }
  }
  _getDeviceList(){
    console.log("Tree._getDeviceList()====>");
    this.deviceNames = [];
    this.devices = {};
    this.wrapper.innerHTML = "";
    let devCnt = 0;

    for(var cnt=0;cnt<this.midi.outputs.length;cnt++){
      let device = this.midi.outputs[cnt].name;
      if(device.startsWith("mi:muz:tree-")){
        devCnt ++;
        let devNameStrArr = device.split("-");
        let _did = devNameStrArr[1];
        this.deviceNames.push({name:device,did:_did});
        this.devices[_did] = {did:_did, deviceName:device};
        console.log("did="+_did);

        const treedom = document.createElement("div");
        treedom.classList.add("treewrap");
        treedom.id = _did;
        treedom.innerHTML = treeSvg;
        this.devices[_did].tree = treedom;
        this.devices[_did].svg = treedom.querySelector(".svgtree");

        this.devices[_did].leds = [];
        for(let cnt=0;cnt<16;cnt++){
          let dom = this.devices[_did].svg.querySelector("#LED-"+cnt);
          this.devices[_did].leds.push(dom);
        }
        this.wrapper.appendChild(treedom);
      }
    }
    let viewWidth = Math.floor(100 / devCnt);
    for(let cnt=0;cnt<this.deviceNames.length;cnt++){
      let did = this.deviceNames[cnt].did;
      console.log("did="+did);
      let treeHeight = this.devices[did].tree.clientHeight;
      let svgHeight = this.devices[did].svg.clientHeight;
      console.log("tree="+treeHeight+" svg="+svgHeight);
      let heightDiv = 100 * (treeHeight / svgHeight);
      let size;
      if(heightDiv > viewWidth){
        size = viewWidth;
      }else{
        size = heightDiv;
      }
      this.devices[did].svg.style.width = "100%";
      this.devices[did].tree.style.width = size+"%";
    }
  }
  _onChange(){
    console.log("Tree._onChange()");
    this._getDeviceList();
    if(this.onChange != null){
      this.onChange(this.deviceNames);
    }
  }
  setOnChange(func){
    console.log("Tree.setOnChange()");
    this.onChange = func;
  }
  fill(did, led, color){
    console.log("Tree.fill()");
    if(did != null){
      this.devices[did].leds[led].style.fill = color;
    }else{
      for(let cnt=0;cnt=this.deviceNames.length;cnt++){
        let did = this.deviceNames[cnt].did;
        this.devices[did].leds[led].style.fill = color;
      }
    }
  }
  clear(did, led){
    console.log("Tree.clear()");
    this.devices[did].leds[led].style.fill = "#000000";
  }
  clearAll(did){
    console.log("Tree.clearAll()");

    this.clearViewAll(did);

    let deviceName = (did == null)? null : this.devices[did].deviceName;

    if(deviceName == null){
      this.midi.sendNoteOff(1,0,0);
    }else{
      this.midi.sendNoteOff(1,0,0,[deviceName]);
    }
  }
  clearViewAll(did){
    console.log("Tree.clearViewAll()");
    if(did != null){
      for(let cnt=0;cnt<16;cnt++){
        this.clear(did,cnt);        
      }
    }else{
      for(let cnt=0;cnt<this.deviceNames.length;cnt++){
        let _did = this.deviceNames[cnt].did;
        for(let cnt2=0;cnt2<16;cnt2++){
          this.clear(_did,cnt2);        
        }
      }
    }
  }
  view(did,pat10,pat1,color,at){
    if(arguments.length > 4){
      let now = performance.now();
      let delay = Math.floor(at - now);
      setTimeout(()=>{
        this._view(did,pat10,pat1,color);
      },delay);
    }else{
      this._view(did,pat10,pat1,color);
    }
  }
  _view(did,pat10,pat1,color){
    let pat = PATS[pat10][pat1];
    this.clearViewAll(did);
    for(let cnt=0;cnt<pat.length;cnt++){
      this.fill(did,pat[cnt],color);
    }
  }
  viewAll(pat10,pat1,color,at){
    console.log("Tree.viewAll()");
    if(arguments.length > 3){
      let now = performance.now();
      let delay = Math.floor(at - now);
      setTimeout(()=>{
        this._viewAll(pat10,pat1,color,at);
      },delay);      
    }else{
      this._viewAll(pat10,pat1,color,at);
    }
  }
  _viewAll(pat10,pat1,color,at){
    console.log("Tree._viewAll()");
    for(let cnt1=0;cnt1<this.deviceNames.length;cnt1++){
      let did = this.deviceNames[cnt1].did;
      this.view(did,pat10,pat1,color);
    }
  }
  send(did, colorId, pat10, pat1, at){
    console.log("Tree.send()");
    let color = colorId % COLORS.length;
    let pat10idx = pat10;
    let pat1idx = pat1;
    if(pat10idx >= PATS.length){
      console.log("send pat10 error");
      return;
    }
    if(pat1idx >= PATS[pat10idx].length){
      console.log("send pat1 error");
      return;
    }
    let midiValue = ((pat10idx+1)*10)+pat1idx;
    let deviceName = (did == null)? null : this.devices[did].deviceName;
    if(arguments.length > 5){
      if(deviceName == null){
        this.midi.sendNoteOnAt(at,1,color,midiValue);
      }else{
        this.midi.sendNoteOnAt(at,1,color,midiValue,[deviceName]);
      }
    }else{
      if(deviceName == null){
        this.midi.sendNoteOn(1,color,midiValue);
        this.viewAll(pat10,pat1,COLORS[color].data);
      }else{
        this.midi.sendNoteOn(1,color,midiValue,[deviceName]);
        this.view(did,pat10,pat1,COLORS[color].data);
      }
    }
  }
  wait(ms){
    return new Promise((resolve)=>{setTimeout(resolve,ms);});
  }
  
}

export default Tree;