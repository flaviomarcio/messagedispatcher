/*
Requisição 
Verificar sessão se conta já existe

Request_body
	Montagem, Usar tirar md5 do codigo da conta(documento, cpf,e-mail, etc) para e prencher na body com "hsh_account"
	body:{"hsh_account": "476869598e748d958e819c180af31982"}

Response_body
	status_code: 200
	body:{"hsh_salt": "153c6efa7255f9c18f5bf29b64a60331"}
*/


Post: http://127.0.0.1:8080/v1/acl/account/person_verify

[
    {
        "resquest": {
            "body": {
                "hsh_account": "476869598e748d958e819c180af31982"
            },
            "header": {
                "Content-Type": "application/json"
            },
            "method": "Post",
            "start": "2020-04-19T23:35:36.792",
            "url": "http://127.0.0.1:8080/v1/acl/account/person_verify"
        }
    },
    {
        "response": {
            "body": {
                "hsh_salt": "153c6efa7255f9c18f5bf29b64a60331"
            },
            "finish": "2020-04-19T23:35:36.813",
            "header": {
            },
            "qt_status_code": 0,
            "status_code": 200,
            "status_reason_phrase": null
        }
    }
]

/*
Requisição 
Registrar novo usuário

Request_body
	Montagem, Usar tirar md5 do codigo da conta(documento, cpf,e-mail, etc) para e prencher na body com "hsh_account"
	body:{"hsh_account": "476869598e748d958e819c180af31982"}

Response_body
	status_code: 200
	body:{
             "e_mail": "test@test.org",
            ,"hsh_account": "476869598e748d958e819c180af31982",
            ,"hsh_pwd": "1669198dbf6ea910ecce0172e14e7e52",
            ,"name": "person"
		 }
*/

Post: http://127.0.0.1:8080/v1/acl/account/person_register
[
    {
        "resquest": {
            "body": {
                "e_mail": "test@test.org",
                "hsh_account": "476869598e748d958e819c180af31982",
                "hsh_pwd": "1669198dbf6ea910ecce0172e14e7e52",
                "name": "person"
            },
            "header": {
                "Content-Type": "application/json"
            },
            "method": "Post",
            "start": "2020-04-19T23:35:36.814",
            "url": "http://127.0.0.1:8080/v1/acl/account/person_register"
        }
    },
    {
        "response": {
            "body": {
                "dt_rev": "2020-04-19T23:35:36.825",
                "e_mail": "test@test.org",
                "hsh_account": "476869598e748d958e819c180af31982",
                "name": "person",
                "rev": "5e3f03b4-d150-58b8-84c8-c269f4dc2817",
                "uuid": "7eadfdc2-1bf8-5cd9-953b-469de7dd2155"
            },
            "finish": "2020-04-19T23:35:36.829",
            "header": {
            },
            "qt_status_code": 0,
            "status_code": 200,
            "status_reason_phrase": null
        }
    }
]


/*
Requisição 
Requisição de salt para teste da senha para login

Request_body
	Montagem, Usar tirar md5 do codigo da conta(documento, cpf,e-mail, etc) para e prencher na body com "hsh_account"
	body:{"hsh_account": "476869598e748d958e819c180af31982"}

Response_body
	status_code: 200
	body:{"hsh_salt": "153c6efa7255f9c18f5bf29b64a60331"}
*/


Post: http://127.0.0.1:8080/v1/acl/session/salt
[
    {
        "resquest": {
            "body": {
                "hsh_account": "476869598e748d958e819c180af31982"
            },
            "header": {
                "Content-Type": "application/json"
            },
            "method": "Post",
            "start": "2020-04-19T23:35:36.831",
            "url": "http://127.0.0.1:8080/v1/acl/session/salt"
        }
    },
    {
        "response": {
            "body": {
                "hsh_salt": "ad70bc78243cf0531ef42d447908978d"
            },
            "finish": "2020-04-19T23:35:36.844",
            "header": {
            },
            "qt_status_code": 0,
            "status_code": 200,
            "status_reason_phrase": null
        }
    }
]


/*
Requisição 
Requisição de salt para teste da senha para login

Request_body
	Montagem
		Usar tirar md5 do codigo da conta(documento, cpf,e-mail, etc) para e prencher na body com "hsh_account"
		Usar hsh_salt, contatenar com hsh_pwd e tirar o md5 e colocar na body com "hsh_salt_pwd"


	body:{"hsh_account": "476869598e748d958e819c180af31982", "hsh_salt_pwd": "4959361f72cb3bd46ef04364b4d2f4f5"}

Response_body
	status_code: 200
    body: {
        "hsh_md5": "0e162fc4fbedc9c08f9aef5b81161729",
        "hsh_salt": "269edda046378bc7fd424382ca18d92d",
        "payload": {
            "datetime": "2020-04-19T23:35:36.853",
            "hsh_account": "476869598e748d958e819c180af31982",
            "hsh_salt_pwd": "4959361f72cb3bd46ef04364b4d2f4f5"
        }
    }
*/


Post: http://127.0.0.1:8080/v1/acl/session/login
[
    {
        "resquest": {
            "body": {
                "hsh_account": "476869598e748d958e819c180af31982",
                "hsh_salt_pwd": "4959361f72cb3bd46ef04364b4d2f4f5"
            },
            "header": {
                "Content-Type": "application/json"
            },
            "method": "Post",
            "start": "2020-04-19T23:35:36.846",
            "url": "http://127.0.0.1:8080/v1/acl/session/login"
        }
    },
    {
        "response": {
            "body": {
                "hsh_md5": "0e162fc4fbedc9c08f9aef5b81161729",
                "hsh_salt": "269edda046378bc7fd424382ca18d92d",
                "payload": {
                    "datetime": "2020-04-19T23:35:36.853",
                    "hsh_account": "476869598e748d958e819c180af31982",
                    "hsh_salt_pwd": "4959361f72cb3bd46ef04364b4d2f4f5"
                }
            },
            "finish": "2020-04-19T23:35:36.863",
            "header": {
            },
            "qt_status_code": 0,
            "status_code": 200,
            "status_reason_phrase": null
        }
    }
]



/*
Requisição 
Requisição das sessoes ativas no sistema

Request_body
	Montagem
		Usar tirar md5 do codigo da conta(documento, cpf,e-mail, etc) para e prencher na body com "hsh_account"
		Usar dados recuperados no login
			User hsh_md5 para enviar no bady em "hsh_md5"
			Usar hsh_salt, contatenar com hsh_md5 e tirar o md5 e colocar na body com "hsh_salt_pwd"

	body: {
               "hsh_account": "476869598e748d958e819c180af31982",
               "hsh_md5": "0e162fc4fbedc9c08f9aef5b81161729",
               "hsh_salt": "8350393896bea88370ba5a315d6213a1"
          }

Response_body
	status_code: 200
    body: [
                {
                    "dt": "2020-04-19T00:00:00.000",
                    "hsh_md5": "0e162fc4fbedc9c08f9aef5b81161729",
                    "hsh_salt": "710ffca7b87de4f0abfb14919adf2dac",
                    "hsh_salt_dyn": "22221271f46816ea4c7cc2905c1e595d",
                    "state": 1,
                    "token_uuid": "4c8aee0c-c74d-5991-9330-0e5dea22395e",
                    "user_uuid": "7eadfdc2-1bf8-5cd9-953b-469de7dd2155",
                    "uuid": "63530c50-aba7-5b4b-bb2a-a5d98df9fb4c"
                }
           ]
*/


Post: http://127.0.0.1:8080/v1/acl/session/sessions
[
    {
        "resquest": {
            "body": {
                "hsh_account": "476869598e748d958e819c180af31982",
                "hsh_md5": "0e162fc4fbedc9c08f9aef5b81161729",
                "hsh_salt": "8350393896bea88370ba5a315d6213a1"
            },
            "header": {
                "Content-Type": "application/json"
            },
            "method": "Post",
            "start": "2020-04-19T23:35:36.865",
            "url": "http://127.0.0.1:8080/v1/acl/session/sessions"
        }
    },
    {
        "response": {
            "body": [
                {
                    "dt": "2020-04-19T00:00:00.000",
                    "hsh_md5": "0e162fc4fbedc9c08f9aef5b81161729",
                    "hsh_salt": "710ffca7b87de4f0abfb14919adf2dac",
                    "hsh_salt_dyn": "22221271f46816ea4c7cc2905c1e595d",
                    "state": 1,
                    "token_uuid": "4c8aee0c-c74d-5991-9330-0e5dea22395e",
                    "user_uuid": "7eadfdc2-1bf8-5cd9-953b-469de7dd2155",
                    "uuid": "63530c50-aba7-5b4b-bb2a-a5d98df9fb4c"
                }
            ],
            "finish": "2020-04-19T23:35:36.906",
            "header": {
            },
            "qt_status_code": 0,
            "status_code": 200,
            "status_reason_phrase": null
        }
    }
]

/*
Requisição 
Requisição para validar se sessao está ativa

Request_body
	Montagem
		Usar tirar md5 do codigo da conta(documento, cpf,e-mail, etc) para e prencher na body com "hsh_account"
		Usar dados recuperados no login
			User hsh_md5 para enviar no bady em "hsh_md5"
			Usar hsh_salt, contatenar com hsh_md5 e tirar o md5 e colocar na body com "hsh_salt_pwd"

	body: {
               "hsh_account": "476869598e748d958e819c180af31982",
               "hsh_md5": "0e162fc4fbedc9c08f9aef5b81161729",
               "hsh_salt": "8350393896bea88370ba5a315d6213a1"
          }

Response_body
	status_code: 200
    body: null
*/


Post: http://127.0.0.1:8080/v1/acl/session/verify
[
    {
        "resquest": {
            "body": {
                "hsh_account": "476869598e748d958e819c180af31982",
                "hsh_md5": "0e162fc4fbedc9c08f9aef5b81161729",
                "hsh_salt": "8350393896bea88370ba5a315d6213a1"
            },
            "header": {
                "Content-Type": "application/json"
            },
            "method": "Post",
            "start": "2020-04-19T23:35:36.908",
            "url": "http://127.0.0.1:8080/v1/acl/session/verify"
        }
    },
    {
        "response": {
            "body": null,
            "finish": "2020-04-19T23:35:36.939",
            "header": {
            },
            "qt_status_code": 0,
            "status_code": 200,
            "status_reason_phrase": null
        }
    }
]


/*
Requisição 
Requisição para encerrar sessão

Request_body
	Montagem
		Usar tirar md5 do codigo da conta(documento, cpf,e-mail, etc) para e prencher na body com "hsh_account"
		Usar dados recuperados no login
			User hsh_md5 para enviar no bady em "hsh_md5"
			Usar hsh_salt, contatenar com hsh_md5 e tirar o md5 e colocar na body com "hsh_salt_pwd"

	body: {
               "hsh_account": "476869598e748d958e819c180af31982",
               "hsh_md5": "0e162fc4fbedc9c08f9aef5b81161729",
               "hsh_salt": "8350393896bea88370ba5a315d6213a1"
          }

Response_body
	status_code: 200
    body: null
*/


Post: http://127.0.0.1:8080/v1/acl/session/logout
[
    {
        "resquest": {
            "body": {
                "hsh_account": "476869598e748d958e819c180af31982",
                "hsh_md5": "0e162fc4fbedc9c08f9aef5b81161729",
                "hsh_salt": "8350393896bea88370ba5a315d6213a1"
            },
            "header": {
                "Content-Type": "application/json"
            },
            "method": "Post",
            "start": "2020-04-19T23:35:36.941",
            "url": "http://127.0.0.1:8080/v1/acl/session/logout"
        }
    },
    {
        "response": {
            "body": null,
            "finish": "2020-04-19T23:35:36.966",
            "header": {
            },
            "qt_status_code": 0,
            "status_code": 200,
            "status_reason_phrase": null
        }
    }
]

/*
Requisição 
Requisição para cancelar assinatura do usuário

Request_body
	Montagem
		Usar tirar md5 do codigo da conta(documento, cpf,e-mail, etc) para e prencher na body com "hsh_account"
		Usar dados recuperados no login
			User hsh_md5 para enviar no bady em "hsh_md5"
			Usar hsh_salt, contatenar com hsh_md5 e tirar o md5 e colocar na body com "hsh_salt_pwd"

	body: {
               "hsh_account": "476869598e748d958e819c180af31982",
               "hsh_md5": "0e162fc4fbedc9c08f9aef5b81161729",
               "hsh_salt": "8350393896bea88370ba5a315d6213a1"
          }

Response_body
	status_code: 200
    body: null
*/

Post: http://127.0.0.1:8080/v1/acl/account/person_unregister
[
    {
        "resquest": {
            "body": {
                "hsh_account": "476869598e748d958e819c180af31982",
                "hsh_md5": "3989ce88233f2400decc585720966d05",
                "hsh_salt": "0c3c6e90087f71f5fd08d6a453c64e44"
            },
            "header": {
                "Content-Type": "application/json"
            },
            "method": "Post",
            "start": "2020-04-19T23:35:37.027",
            "url": "http://127.0.0.1:8080/v1/acl/account/person_unregister"
        }
    },
    {
        "response": {
            "body": null,
            "finish": "2020-04-19T23:35:37.237",
            "header": {
            },
            "qt_status_code": 0,
            "status_code": 200,
            "status_reason_phrase": null
        }
    }
]


