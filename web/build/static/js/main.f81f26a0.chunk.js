(this["webpackJsonpml-log-web"]=this["webpackJsonpml-log-web"]||[]).push([[0],{100:function(e,t,a){"use strict";a.r(t);var n=a(7),r=a(0),s=a(10),i=a.n(s),c=(a(86),a(30)),o=a(140),l=a(141),u=a(142),j=a(143),d=a(150),b=a(147),p=a(149),h=a(146),f=a(72),m=a(138),x=a(139),g=a(137),v=a(71),O=a(11),w=a(70),I=a.n(w),S=a(45),y=a(63),N=new(function(){function e(){Object(S.a)(this,e),this._events={}}return Object(y.a)(e,[{key:"on",value:function(e,t){this._events[e]||(this._events[e]=[]),this._events[e].push(t)}},{key:"removeListener",value:function(e,t){if(this._events[e]){this._events[e]=this._events[e].filter((function(e){return e!==t}))}}},{key:"emit",value:function(e,t){if(this._events[e]){this._events[e].forEach((function(e){e(t)}))}}}]),e}()),P=new function e(){Object(S.a)(this,e),this.applicationName=localStorage.getItem("mlLogApplicationName")||"",this.redisHost=localStorage.getItem("mlLogRedisHost")||"",this.redisPort=localStorage.getItem("mlLogRedisPort")||0,this.redisDatabaseIndex=localStorage.getItem("mlLogRedisDatabaseIndex")||0},L=a(42),k=a.n(L),R=a(56),C=a(64),D=a.n(C),_=a(133),H=a(65);function B(){return E.apply(this,arguments)}function E(){return(E=Object(R.a)(k.a.mark((function e(){var t,a;return k.a.wrap((function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,fetch("".concat(H.endpoint,"/api/query/xy-items?")+new URLSearchParams({applicationName:P.applicationName,redisHost:P.redisHost,redisPort:P.redisPort,redisDatabaseIndex:P.redisDatabaseIndex}));case 2:return t=e.sent,e.next=5,t.json();case 5:return a=e.sent,e.abrupt("return",a);case 7:case"end":return e.stop()}}),e)})))).apply(this,arguments)}var F=function(){var e=Object(r.useState)([]),t=Object(c.a)(e,2),a=t[0],s=t[1];return Object(r.useEffect)((function(){var e=function(){var e=Object(R.a)(k.a.mark((function e(){var t;return k.a.wrap((function(e){for(;;)switch(e.prev=e.next){case 0:return e.next=2,B();case 2:t=e.sent,s(t);case 4:case"end":return e.stop()}}),e)})));return function(){return e.apply(this,arguments)}}();e(),N.on("refresh-plots",(function(){e()}))}),[]),Object(n.jsx)("div",{children:Object(n.jsx)(_.a,{container:!0,spacing:3,children:a.map((function(e,t){return Object(n.jsx)(_.a,{item:!0,md:12,lg:6,children:Object(n.jsx)(D.a,{data:[{x:e.items.map((function(e){return e.x})),y:e.items.map((function(e){return e.y})),type:"scatter",mode:"lines+markers"}],layout:{title:e.key}})},t)}))})})},A=(a(94),Object(f.a)({palette:{primary:{main:g.a[900]}}})),J=Object(m.a)((function(e){return{root:{display:"flex"},appBar:{zIndex:e.zIndex.drawer+1},drawer:{width:240,flexShrink:0},drawerPaper:{width:240},drawerContainer:{overflow:"auto",padding:e.spacing(2)},content:{flexGrow:1,padding:e.spacing(3)},title:{flexGrow:1}}}));var z=function(){var e=J(),t=Object(r.useState)(P.applicationName),a=Object(c.a)(t,2),s=a[0],i=a[1],f=Object(r.useState)(P.redisHost),m=Object(c.a)(f,2),g=m[0],w=m[1],S=Object(r.useState)(P.redisPort),y=Object(c.a)(S,2),L=y[0],k=y[1],R=Object(r.useState)(P.redisDatabaseIndex),C=Object(c.a)(R,2),D=C[0],_=C[1];return Object(r.useEffect)((function(){setInterval((function(){N.emit("refresh-plots",{})}),1e3)})),Object(n.jsx)(x.a,{theme:A,children:Object(n.jsxs)("div",{className:e.root,children:[Object(n.jsx)(o.a,{}),Object(n.jsx)(l.a,{position:"fixed",className:e.appBar,children:Object(n.jsxs)(u.a,{children:[Object(n.jsx)(j.a,{variant:"h6",className:e.title,children:"ml-log"}),Object(n.jsx)(d.a,{title:"Refresh plots",children:Object(n.jsx)(b.a,{color:"inherit",onClick:function(){N.emit("refresh-plots",{})},children:Object(n.jsx)(I.a,{})})})]})}),Object(n.jsxs)(p.a,{className:e.drawer,variant:"permanent",classes:{paper:e.drawerPaper},children:[Object(n.jsx)(u.a,{}),Object(n.jsxs)("div",{className:e.drawerContainer,children:[Object(n.jsx)(h.a,{label:"Application Name",variant:"outlined",value:s,onChange:function(e){i(e.target.value),P.applicationName=e.target.value,localStorage.setItem("mlLogApplicationName",e.target.value)}}),Object(n.jsx)("br",{}),Object(n.jsx)("br",{}),Object(n.jsx)(h.a,{label:"Redis Host",variant:"outlined",value:g,onChange:function(e){w(e.target.value),P.redisHost=e.target.value,localStorage.setItem("mlLogRedisHost",e.target.value)}}),Object(n.jsx)("br",{}),Object(n.jsx)("br",{}),Object(n.jsx)(h.a,{label:"Redis Port",variant:"outlined",value:L,onChange:function(e){k(e.target.value),P.redisPort=e.target.value,localStorage.setItem("mlLogRedisPort",e.target.value)}}),Object(n.jsx)("br",{}),Object(n.jsx)("br",{}),Object(n.jsx)(h.a,{label:"Redis Database Index",variant:"outlined",value:D,onChange:function(e){_(e.target.value),P.redisDatabaseIndex=e.target.value,localStorage.setItem("mlLogRedisDatabaseIndex",e.target.value)}})]})]}),Object(n.jsxs)("main",{className:e.content,children:[Object(n.jsx)(u.a,{}),Object(n.jsx)(v.a,{children:Object(n.jsx)(O.c,{children:Object(n.jsx)(O.a,{path:"/",exact:!0,component:F})})})]})]})})},G=function(e){e&&e instanceof Function&&a.e(3).then(a.bind(null,151)).then((function(t){var a=t.getCLS,n=t.getFID,r=t.getFCP,s=t.getLCP,i=t.getTTFB;a(e),n(e),r(e),s(e),i(e)}))};i.a.render(Object(n.jsx)(z,{}),document.getElementById("root")),G(console.log)},65:function(e){e.exports=JSON.parse('{"endpoint":"http://localhost:3005"}')},86:function(e,t,a){},94:function(e,t,a){}},[[100,1,2]]]);
//# sourceMappingURL=main.f81f26a0.chunk.js.map